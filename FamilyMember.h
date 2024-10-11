#ifndef FAMILYMEMBER_H
#define FAMILYMEMBER_H

#include <iostream>
#include <string>
#include <vector>

class FamilyMember {
public:
    FamilyMember();
    FamilyMember(const std::string& name, const std::string& birthDate, const std::string& deathDate = "");
    FamilyMember(const FamilyMember& other);
    ~FamilyMember();

    void display() const;
    void save(std::ostream& out) const;
    void load(std::istream& in);

    void setName(const std::string& name);
    void setBirthDate(const std::string& birthDate);
    void setDeathDate(const std::string& deathDate);
    void setParents(const std::vector<FamilyMember*>& parents);
    void setSpouse(FamilyMember* spouse);
    void setChildren(const std::vector<FamilyMember*>& children);

    std::string getName() const;
    std::string getBirthDate() const;
    std::string getDeathDate() const;
    std::vector<FamilyMember*> getParents() const;
    FamilyMember* getSpouse() const;
    std::vector<FamilyMember*> getChildren() const;
    int getAge() const;

private:
    std::string name;
    std::string birthDate;
    std::string deathDate;
    std::vector<FamilyMember*> parents;
    FamilyMember* spouse;
    std::vector<FamilyMember*> children;

    int calculateAge() const;
};

#endif // FAMILYMEMBER_H
