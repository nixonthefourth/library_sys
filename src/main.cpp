#include "Logic/LibrarySystem.h"
#include <iostream>

int main() {
    LibrarySystem system;
    system.loadData();

    int choice;

    while (true) {
        std::cout << "\n1. Borrow\n2. Return\n3. List Available\n4. Loan Report\n5. User Report\n0. Exit\n";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int userID;
            std::string resourceID;

            std::cout << "Enter user ID: ";
            std::cin >> userID;

            std::cout << "Enter resource ID: ";
            std::cin >> resourceID;

            system.borrowResource(userID, resourceID);
        }

        else if (choice == 2) {
            int userID;
            std::string resourceID;

            std::cout << "Enter user ID: ";
            std::cin >> userID;

            std::cout << "Enter resource ID: ";
            std::cin >> resourceID;

            system.returnResource(userID, resourceID);
        }

        else if (choice == 3) {
            system.listAvailableResources();
        }

        else if (choice == 4) {
            system.reportLoanedResources();
        }

        else if (choice == 5) {
            system.reportUsersWithLoans();
        }
    }

    return 0;
}