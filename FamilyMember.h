#ifndef FAMILYMEMBER_H
#define FAMILYMEMBER_H

#include <iostream>
#include <string>
#include <vector>

class FamilyMember {
public:
    FamilyMember();
    FamilyMember(const std::string& firstName, const std::string& lastName, const std::string& patronymic, const std::string& birthDate, const std::string& deathDate = "alive");
    FamilyMember(const FamilyMember& other);
    ~FamilyMember();

    void display() const;
    void save(std::ostream& out) const;
    void load(std::istream& in);

    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPatronymic(const std::string& patronymic);
    void setBirthDate(const std::string& birthDate);
    void setDeathDate(const std::string& deathDate);
    void setParents(const std::vector<FamilyMember*>& parents);
    void setSpouse(FamilyMember* spouse);
    void setChildren(const std::vector<FamilyMember*>& children);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPatronymic() const;
    std::string getBirthDate() const;
    std::string getDeathDate() const;
    std::vector<FamilyMember*> getParents() const;
    FamilyMember* getSpouse() const;
    std::vector<FamilyMember*> getChildren() const;
    int getAge() const;

private:
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string birthDate;
    std::string deathDate;
    std::vector<FamilyMember*> parents;
    FamilyMember* spouse;
    std::vector<FamilyMember*> children;

    int calculateAge() const;
};

#endif // FAMILYMEMBER_H
