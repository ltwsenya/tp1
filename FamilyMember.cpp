#include "FamilyMember.h"
#include <sstream>
#include <ctime>
#include <iomanip> // Добавьте этот заголовочный файл

FamilyMember::FamilyMember() : name(""), birthDate(""), deathDate(""), spouse(nullptr) {
    std::cout << "FamilyMember default constructor called" << std::endl;
}

FamilyMember::FamilyMember(const std::string& name, const std::string& birthDate, const std::string& deathDate)
        : name(name), birthDate(birthDate), deathDate(deathDate), spouse(nullptr) {
    std::cout << "FamilyMember parameterized constructor called" << std::endl;
}

FamilyMember::FamilyMember(const FamilyMember& other)
        : name(other.name), birthDate(other.birthDate), deathDate(other.deathDate), parents(other.parents), spouse(other.spouse), children(other.children) {
    std::cout << "FamilyMember copy constructor called" << std::endl;
}

FamilyMember::~FamilyMember() {
    std::cout << "FamilyMember destructor called" << std::endl;
}

void FamilyMember::display() const {
    std::cout << "Name: " << name << ", Birth Date: " << birthDate << ", Death Date: " << deathDate << ", Age: " << getAge() << std::endl;
}

void FamilyMember::save(std::ostream& out) const {
    out << name << " " << birthDate << " " << deathDate;
}

void FamilyMember::load(std::istream& in) {
    in >> name >> birthDate >> deathDate;
}

void FamilyMember::setName(const std::string& name) {
    this->name = name;
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

std::string FamilyMember::getName() const {
    return name;
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

    int age = current->tm_year + 1900 - birth.tm_year;
    if (current->tm_mon < birth.tm_mon || (current->tm_mon == birth.tm_mon && current->tm_mday < birth.tm_mday)) {
        --age;
    }

    if (!deathDate.empty()) {
        std::tm death = {};
        std::istringstream ss(deathDate);
        ss >> std::get_time(&death, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::runtime_error("Invalid death date format");
        }

        age = death.tm_year + 1900 - birth.tm_year;
        if (death.tm_mon < birth.tm_mon || (death.tm_mon == birth.tm_mon && death.tm_mday < birth.tm_mday)) {
            --age;
        }
    }

    return age;
}