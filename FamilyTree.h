#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include "FamilyMember.h"

class FamilyTree {
public:
    FamilyTree();
    ~FamilyTree();

    void addMember(FamilyMember* member);
    void removeMember(int index);
    void displayMembers() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void editMember(int index);


private:
    FamilyMember** members;
    int size;
    int capacity;

    void resize();
    bool isDateValid(const std::string& date);
    bool isBirthDateValid(const std::string& birthDate);
};

#endif // FAMILYTREE_H
