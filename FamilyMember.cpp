#include "FamilyMember.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>

FamilyMember::FamilyMember() : firstName(""), lastName(""), patronymic(""), birthDate(""), deathDate("alive"), spouse(nullptr) {
    std::cout << "FamilyMember default constructor called" << std::endl;
}

FamilyMember::FamilyMember(const std::string& firstName, const std::string& lastName, const std::string& patronymic, const std::string& birthDate, const std::string& deathDate)
        : firstName(firstName), lastName(lastName), patronymic(patronymic), birthDate(birthDate), deathDate(deathDate), spouse(nullptr) {
    std::cout << "FamilyMember parameterized constructor called" << std::endl;
}

FamilyMember::FamilyMember(const FamilyMember& other)
        : firstName(other.firstName), lastName(other.lastName), patronymic(other.patronymic), birthDate(other.birthDate), deathDate(other.deathDate), parents(other.parents), spouse(other.spouse), children(other.children) {
    std::cout << "FamilyMember copy constructor called" << std::endl;
}

FamilyMember::~FamilyMember() {
    std::cout << "FamilyMember destructor called" << std::endl;
}

void FamilyMember::display() const {
    std::cout << "Name: " << firstName << " " << patronymic << " " << lastName << ", Birth Date: " << birthDate << ", Death Date: " << deathDate << ", Age: " << getAge() << std::endl;
    std::cout << "Parents: ";
    for (size_t i = 0; i < parents.size(); ++i) {
        std::cout << parents[i]->getFirstName() << " " << parents[i]->getLastName();
        if (i < parents.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Spouse: ";
    if (spouse) {
        std::cout << spouse->getFirstName() << " " << spouse->getLastName() << std::endl;
    } else {
        std::cout << "None" << std::endl;
    }
    std::cout << "Children: ";
    for (size_t i = 0; i < children.size(); ++i) {
        std::cout << children[i]->getFirstName() << " " << children[i]->getLastName();
        if (i < children.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void FamilyMember::save(std::ostream& out) const {
    out << firstName << " " << lastName << " " << patronymic << " " << birthDate << " " << deathDate << " ";
    out << parents.size() << " ";
    for (const auto& parent : parents) {
        parent->save(out);
    }
    if (spouse) {
        out << "1 ";
        spouse->save(out);
    } else {
        out << "0 ";
    }
    out << children.size() << " ";
    for (const auto& child : children) {
        child->save(out);
    }
}

void FamilyMember::load(std::istream& in) {
    in >> firstName >> lastName >> patronymic >> birthDate >> deathDate;
    int numParents;
    in >> numParents;
    parents.clear();
    for (int i = 0; i < numParents; ++i) {
        FamilyMember* parent = new FamilyMember();
        parent->load(in);
        parents.push_back(parent);
    }
    int hasSpouse;
    in >> hasSpouse;
    if (hasSpouse) {
        spouse = new FamilyMember();
        spouse->load(in);
    } else {
        spouse = nullptr;
    }
    int numChildren;
    in >> numChildren;
    children.clear();
    for (int i = 0; i < numChildren; ++i) {
        FamilyMember* child = new FamilyMember();
        child->load(in);
        children.push_back(child);
    }
}

void FamilyMember::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void FamilyMember::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void FamilyMember::setPatronymic(const std::string& patronymic) {
    this->patronymic = patronymic;
}

void FamilyMember::setBirthDate(const std::string& birthDate) {
    this->birthDate = birthDate;
}

void FamilyMember::setDeathDate(const std::string& deathDate) {
    this->deathDate = deathDate;
}

void FamilyMember::setParents(const std::vector<FamilyMember*>& parents) {
    this->parents = parents;
}

void FamilyMember::setSpouse(FamilyMember* spouse) {
    this->spouse = spouse;
}

void FamilyMember::setChildren(const std::vector<FamilyMember*>& children) {
    this->children = children;
}

std::string FamilyMember::getFirstName() const {
    return firstName;
}

std::string FamilyMember::getLastName() const {
    return lastName;
}

std::string FamilyMember::getPatronymic() const {
    return patronymic;
}

std::string FamilyMember::getBirthDate() const {
    return birthDate;
}

std::string FamilyMember::getDeathDate() const {
    return deathDate;
}

std::vector<FamilyMember*> FamilyMember::getParents() const {
    return parents;
}

FamilyMember* FamilyMember::getSpouse() const {
    return spouse;
}

std::vector<FamilyMember*> FamilyMember::getChildren() const {
    return children;
}

int FamilyMember::getAge() const {
    return calculateAge();
}

int FamilyMember::calculateAge() const {
    std::tm birth = {};
    std::istringstream ss(birthDate);
    ss >> std::get_time(&birth, "%Y-%m-%d");
    if (ss.fail()) {
        throw std::runtime_error("Invalid birth date format");
    }

    std::time_t now = std::time(nullptr);
    std::tm* current = std::localtime(&now);

    int age = current->tm_year - birth.tm_year;
    if (current->tm_mon < birth.tm_mon || (current->tm_mon == birth.tm_mon && current->tm_mday < birth.tm_mday)) {
        --age;
    }

    if (deathDate != "alive") {
        std::tm death = {};
        std::istringstream ss(deathDate);
        ss >> std::get_time(&death, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::runtime_error("Invalid death date format");
        }

        if (death.tm_year < birth.tm_year ||
            (death.tm_year == birth.tm_year && death.tm_mon < birth.tm_mon) ||
            (death.tm_year == birth.tm_year && death.tm_mon == birth.tm_mon && death.tm_mday < birth.tm_mday)) {
            throw std::runtime_error("Death date cannot be earlier than birth date");
        }

        age = death.tm_year - birth.tm_year;
        if (death.tm_mon < birth.tm_mon || (death.tm_mon == birth.tm_mon && death.tm_mday < birth.tm_mday)) {
            --age;
        }
    }

    return age;
}
