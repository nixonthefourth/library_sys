//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_LIBRARYSYSTEM_H
#define LIBRARY_SYS_LIBRARYSYSTEM_H

#include <vector>
#include "ResourceList.h"
#include "UserList.h"
#include "Loan.h"

/**
 * @brief Top-level controller for the library management system.
 *
 * Owns the three core data structures — a ResourceList, a UserList,
 * and a vector of active Loans — and exposes the six operations that
 * the REPL calls.  All user-facing output is delegated to Display so
 * this class remains purely concerned with business logic.
 */
class LibrarySystem {
private:
    ResourceList resources; /// All resources loaded from file
    UserList users; /// All users loaded from file
    std::vector<Loan> loans; /// Currently active loans

public:

    /**
     * @brief Loads resource and user data from their text files.
     *
     * Must be called once before any other method; behaviour is
     * undefined if borrow / return / report methods are called first.
     */
    void loadData();

    /**
     * @brief Attempts to issue a loan for the given user and resource.
     *
     * @param userID Integer ID of the borrowing user.
     * @param resourceID String ID of the resource (e.g. "B3", "J1").
     * @return true on success; false if the user / resource was not found
     *         or the borrow conditions were not met.
     */
    bool borrowResource(int userID, const std::string& resourceID);

    /**
     * @brief Processes a return for the given user and resource.
     *
     * @param userID Integer ID of the returning user.
     * @param resourceID String ID of the resource being returned.
     * @return true if a matching loan was found and cleared; false otherwise.
     */
    bool returnResource(int userID, const std::string& resourceID);

    /**
     * @brief Prints all resources that are lendable and not currently on loan.
     */
    void listAvailableResources() const;

    /**
     * @brief Prints a report of every resource currently on loan and its borrower.
     */
    void reportLoanedResources() const;

    /**
     * @brief Prints a deduplicated list of all users who have active loans.
     */
    void reportUsersWithLoans() const;
};

#endif //LIBRARY_SYS_LIBRARYSYSTEM_H