//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Logic/LibrarySystem.h"
#include "Display.h"
#include <iostream>
#include <set>

// ────────────────────────────────────────────────────────────────────────────
// Data loading
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Loads resource and user data from their respective text files.
 *
 * Paths are relative to the project root so the executable must be run
 * from there (or from cmake-build-debug with the ../docs prefix present).
 */
void LibrarySystem::loadData() {
    std::cout << Display::DIM << "  Loading resources..." << Display::RESET << "\n";
    resources.loadFromFile("../docs/A2ResourceList.txt");

    std::cout << Display::DIM << "  Loading users..." << Display::RESET << "\n";
    users.loadFromFile("../docs/A2UserList.txt");

    std::cout << "\n";
}

// ────────────────────────────────────────────────────────────────────────────
// Borrowing
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Attempts to create a loan between a user and a resource.
 *
 * Looks up both entities by ID, constructs a Loan, and calls issueLoan().
 * If the loan is issued it is stored in the loans vector.
 *
 * @param userID Integer ID of the borrowing user.
 * @param resourceID String ID of the target resource (e.g. "B3", "J1").
 * @return true if the loan was created; false otherwise.
 */
bool LibrarySystem::borrowResource(int userID, const std::string& resourceID) {
    Person* user = users.findByID(userID);
    Resource* resource = resources.findByID(resourceID);

    if (!user || !resource) {
        Display::error("User or resource not found — check the IDs and try again.");
        return false;
    }

    Loan loan(user, resource);

    if (loan.issueLoan()) {
        loans.push_back(loan);
        Display::success("Loan created — " + resource->getTitle()
                         + " is now checked out to " + user->getName() + ".");

        return true;
    }

    // Give a more specific reason where possible
    if (!resource->getLend()) {
        Display::error("This resource type cannot be borrowed.");
    } else if (resource->getBorrowed()) {
        Display::error("That resource is already on loan.");
    } else {
        Display::error("Borrow limit reached — " + user->getName()
                       + " cannot borrow any more resources.");
    }

    return false;
}

// ────────────────────────────────────────────────────────────────────────────
// Returning
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Locates an active loan by user and resource ID, then processes the return.
 *
 * Iterates the loans vector looking for a matching (userID, resourceID) pair.
 * On a match, returnLoan() is called and the entry is erased from the vector.
 *
 * @param userID Integer ID of the returning user.
 * @param resourceID String ID of the resource being returned.
 * @return true if the loan was found and returned; false otherwise.
 */
bool LibrarySystem::returnResource(int userID, const std::string& resourceID) {
    for (auto it = loans.begin(); it != loans.end(); ++it) {

        if (it->getBorrower()->getID() == userID &&
            it->getResource()->getID() == resourceID) {

            std::string title = it->getResource()->getTitle();
            it->returnLoan();
            loans.erase(it);

            Display::success(title + " returned successfully.");
            return true;
        }
    }

    Display::error("No matching loan found – verify the user ID and resource ID.");
    return false;
}

// ────────────────────────────────────────────────────────────────────────────
// Reports
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Lists every resource that is lendable and not currently borrowed.
 *
 * Conferences (canLend == false) are filtered out automatically.
 * If nothing is available, an empty-state notice is shown instead.
 */
void LibrarySystem::listAvailableResources() const {
    Display::heading("AVAILABLE RESOURCES");

    bool any = false;

    for (auto r : resources.getResources()) {
        if (!r->getBorrowed()) {
            Display::row(r->getID(), r->getTitle());
            any = true;
        }
    }

    if (!any) Display::empty("available resources");
}

/**
 * @brief Reports every resource currently on loan and who has it.
 *
 * Each row shows the resource title and the borrower's name.
 * If there are no active loans an empty-state notice is shown.
 */
void LibrarySystem::reportLoanedResources() const {
    Display::heading("LOAN REPORT");

    if (loans.empty()) {
        Display::empty("active loans");
        return;
    }

    for (const auto& loan : loans) {
        Display::loanRow(loan.getResource()->getTitle(),
                         loan.getBorrower()->getName());
    }
}

/**
 * @brief Reports every user who has at least one active loan.
 *
 * Uses a set to deduplicate: each user appears at most once regardless
 * of how many resources they have borrowed.
 * If no users have loans, an empty-state notice is shown.
 */
void LibrarySystem::reportUsersWithLoans() const {
    Display::heading("USERS WITH ACTIVE LOANS");

    if (loans.empty()) {
        Display::empty("users with loans");
        return;
    }

    std::set<int> seen;

    for (const auto& loan : loans) {
        Person* user = loan.getBorrower();

        // insert() returns false when the key is already in the set,
        // so this naturally de-duplicates without an extra lookup.
        if (seen.insert(user->getID()).second) {
            Display::row(std::to_string(user->getID()), user->getName());
        }
    }
}