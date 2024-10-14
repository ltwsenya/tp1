#include "FamilyTree.h"
#include "FamilyMember.h"
#include <iostream>

void showMenu() {
    std::cout << "1. Add member" << std::endl;
    std::cout << "2. Remove member" << std::endl;
    std::cout << "3. Display members" << std::endl;
    std::cout << "4. Save to file" << std::endl;
    std::cout << "5. Load from file" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

int main() {
    FamilyTree familyTree;
    int choice;
    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Игнорировать оставшиеся символы в буфере ввода
        switch (choice) {
            case 1: {
                std::string firstName, lastName, patronymic, birthDate, deathDate;
                std::cout << "Enter first name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter patronymic: ";
                std::getline(std::cin, patronymic);
                std::cout << "Enter birth date (YYYY-MM-DD): ";
                std::getline(std::cin, birthDate);
                std::cout << "Enter death date (YYYY-MM-DD) or 'alive' if alive: ";
                std::getline(std::cin, deathDate);

                // Создание нового члена семьи
                FamilyMember* newMember = new FamilyMember(firstName, lastName, patronymic, birthDate, deathDate);

                // Ввод родителей
                std::string motherFirstName, motherLastName, fatherFirstName, fatherLastName;
                std::cout << "Enter mother's first name: ";
                std::getline(std::cin, motherFirstName);
                std::cout << "Enter mother's last name: ";
                std::getline(std::cin, motherLastName);
                std::cout << "Enter father's first name: ";
                std::getline(std::cin, fatherFirstName);
                std::cout << "Enter father's last name: ";
                std::getline(std::cin, fatherLastName);
                FamilyMember* mother = new FamilyMember(motherFirstName, motherLastName, "", "", "alive");
                FamilyMember* father = new FamilyMember(fatherFirstName, fatherLastName, "", "", "alive");
                newMember->setParents({mother, father});

                // Ввод супруга
                std::cout << "Enter spouse first name (leave empty if none): ";
                std::string spouseFirstName;
                std::getline(std::cin, spouseFirstName);
                if (!spouseFirstName.empty()) {
                    std::string spouseLastName;
                    std::cout << "Enter spouse last name: ";
                    std::getline(std::cin, spouseLastName);
                    FamilyMember* spouse = new FamilyMember(spouseFirstName, spouseLastName, "", "", "alive");
                    newMember->setSpouse(spouse);
                }

                // Ввод детей
                std::cout << "Enter the number of children: ";
                int numChildren;
                std::cin >> numChildren;
                std::cin.ignore();
                std::vector<FamilyMember*> children;
                for (int i = 0; i < numChildren; ++i) {
                    std::string childFirstName, childLastName;
                    std::cout << "Enter child " << (i + 1) << " first name: ";
                    std::getline(std::cin, childFirstName);
                    std::cout << "Enter child " << (i + 1) << " last name: ";
                    std::getline(std::cin, childLastName);
                    FamilyMember* child = new FamilyMember(childFirstName, childLastName, "", "", "alive");
                    children.push_back(child);
                }
                newMember->setChildren(children);

                familyTree.addMember(newMember);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                try {
                    familyTree.removeMember(index);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 3:
                familyTree.displayMembers();
                break;
            case 4: {
                std::string filename;
                std::cout << "Enter filename to save: ";
                std::getline(std::cin, filename);
                try {
                    familyTree.saveToFile(filename);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Enter filename to load: ";
                std::getline(std::cin, filename);
                try {
                    familyTree.loadFromFile(filename);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
