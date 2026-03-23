//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../../include/Logic/LibrarySystem.h"
#include <iostream>
#include <set>

// Load Data
void LibrarySystem::loadData() {
    std::cout << "Loading resources...\n";
    resources.loadFromFile("../docs/A2ResourceList.txt");

    std::cout << "Loading users...\n";
    users.loadFromFile("../docs/A2UserList.txt");
}

// Borrow Resources
bool LibrarySystem::borrowResource(int userID, const std::string& resourceID) {
    Person* user = users.findByID(userID);
    Resource* resource = resources.findByID(resourceID);

    if (!user || !resource) {
        std::cout << "Invalid user or resource\n";
        return false;
    }

    Loan loan(user, resource);

    if (loan.issueLoan()) {
        loans.push_back(loan);
        std::cout << "Loan successful\n";
        return true;
    }

    std::cout << "Loan failed\n";
    return false;
}

// Return Resources
bool LibrarySystem::returnResource(int userID, const std::string& resourceID) {
    for (auto it = loans.begin(); it != loans.end(); ++it) {

        if (it->getBorrower()->getID() == userID &&
            it->getResource()->getID() == resourceID) {

            it->returnLoan();
            loans.erase(it);

            std::cout << "Return successful\n";
            return true;
            }
    }

    std::cout << "Loan not found\n";
    return false;
}

// List Available Resources
void LibrarySystem::listAvailableResources() const {
    for (auto r : resources.getResources()) {

        if (!r->getBorrowed() && r->getLend()) {
            std::cout << r->getID() << " - " << r->getTitle() << "\n";
        }
    }
}

// Produce Report of Loaned Resources
void LibrarySystem::reportLoanedResources() const {
    for (const auto& loan : loans) {
        std::cout
            << loan.getResource()->getTitle()
            << " borrowed by "
            << loan.getBorrower()->getName()
            << "\n";
    }
}

// Produce Report of Users
void LibrarySystem::reportUsersWithLoans() const {
    std::set<int> seen;

    for (const auto& loan : loans) {

        Person* user = loan.getBorrower();

        if (seen.insert(user->getID()).second) {
            std::cout << user->getID() << " - " << user->getName() << "\n";
        }
    }
}