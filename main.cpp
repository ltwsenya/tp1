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
        switch (choice) {
            case 1: {
                std::string name, birthDate, deathDate;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter birth date (YYYY-MM-DD): ";
                std::cin >> birthDate;
                std::cout << "Enter death date (YYYY-MM-DD) (leave empty if alive): ";
                std::cin >> deathDate;
                familyTree.addMember(new FamilyMember(name, birthDate, deathDate));
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
                std::cin >> filename;
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
                std::cin >> filename;
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
