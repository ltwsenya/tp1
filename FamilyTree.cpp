#include "FamilyTree.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

FamilyTree::FamilyTree() : members(nullptr), size(0), capacity(0) {
    std::cout << "FamilyTree default constructor called" << std::endl;
}

FamilyTree::~FamilyTree() {
    for (int i = 0; i < size; ++i) {
        delete members[i];
    }
    delete[] members;
    std::cout << "FamilyTree destructor called" << std::endl;
}

void FamilyTree::addMember(FamilyMember* member) {
    if (size >= capacity) {
        resize();
    }
    members[size++] = member;
}

void FamilyTree::removeMember(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete members[index];
    for (int i = index; i < size - 1; ++i) {
        members[i] = members[i + 1];
    }
    --size;
}

void FamilyTree::displayMembers() const {
    for (int i = 0; i < size; ++i) {
        members[i]->display();
    }
}

void FamilyTree::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing");
    }
    out << size << std::endl;
    for (int i = 0; i < size; ++i) {
        members[i]->save(out);
        out << std::endl;
    }
    out.close();
    std::cout << "Data successfully saved to file: " << filename << std::endl;
}

void FamilyTree::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading");
    }

    int newSize;
    in >> newSize;
    in.ignore();

    // Удаляем существующих членов семьи, если они есть
    for (int i = 0; i < size; ++i) {
        delete members[i];
    }
    delete[] members;

    size = 0;
    capacity = newSize;
    members = new FamilyMember*[capacity];

    for (int i = 0; i < newSize; ++i) {
        FamilyMember* member = new FamilyMember();
        member->load(in);
        in.ignore();
        addMember(member);
    }
    in.close();
}

void FamilyTree::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    FamilyMember** newMembers = new FamilyMember*[capacity];
    for (int i = 0; i < size; ++i) {
        newMembers[i] = members[i];
    }
    delete[] members;
    members = newMembers;
}

// Функция проверки корректности формата даты
bool FamilyTree::isDateValid(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

// Функция проверки, что дата рождения не превышает текущую дату
bool FamilyTree::isBirthDateValid(const std::string& birthDate) {
    std::tm birth = {};
    std::istringstream ss(birthDate);
    ss >> std::get_time(&birth, "%Y-%m-%d");

    if (ss.fail()) return false;

    auto t = std::time(nullptr);
    auto* current = std::localtime(&t);

    return (birth.tm_year < current->tm_year) ||
           (birth.tm_year == current->tm_year && birth.tm_mon < current->tm_mon) ||
           (birth.tm_year == current->tm_year && birth.tm_mon == current->tm_mon && birth.tm_mday <= current->tm_mday);
}

void FamilyTree::editMember(int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Invalid index provided." << std::endl;
        return;
    }

    FamilyMember* member = members[index];
    std::string input;

    // Modify first name
    std::cout << "Current First Name: " << member->getFirstName()
              << ". Enter new First Name (or press Enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) member->setFirstName(input);

    // Modify last name
    std::cout << "Current Last Name: " << member->getLastName() << ". Enter new Last Name (or press Enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) member->setLastName(input);

    // Modify patronymic
    std::cout << "Current Patronymic: " << member->getPatronymic()
              << ". Enter new Patronymic (or press Enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) member->setPatronymic(input);

    // Modify birth date
    bool validBirthDate = false;
    while (!validBirthDate) {
        std::cout << "Current Birth Date: " << member->getBirthDate()
                  << ". Enter new Birth Date (YYYY-MM-DD) or press Enter to skip: ";
        std::getline(std::cin, input);
        if (input.empty()) break;
        if (isDateValid(input) && isBirthDateValid(input)) {
            member->setBirthDate(input);
            validBirthDate = true;
        } else {
            std::cerr << "Invalid birth date. Please try again." << std::endl;
        }
    }
}
