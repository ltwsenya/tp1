#include "FamilyTree.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

FamilyTree::FamilyTree() : members(nullptr), size(0), capacity(0) {}

FamilyTree::~FamilyTree() {
    for (int i = 0; i < size; ++i) {
        delete members[i];
    }
    delete[] members;
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
    out.close(); // Убедитесь, что файл закрыт после записи
}

void FamilyTree::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading");
    }
    int newSize;
    in >> newSize;
    in.ignore(); // Игнорировать символ новой строки
    for (int i = 0; i < size; ++i) {
        delete members[i];
    }
    size = 0;
    capacity = 0;
    delete[] members;
    members = nullptr;

    for (int i = 0; i < newSize; ++i) {
        FamilyMember* member = new FamilyMember();
        member->load(in);
        in.ignore(); // Игнорировать символ новой строки
        addMember(member);
    }
    in.close(); // Убедитесь, что файл закрыт после чтения
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
