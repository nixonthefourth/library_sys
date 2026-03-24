//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_LIBRARYSYSTEM_H
#define LIBRARY_SYS_LIBRARYSYSTEM_H

#include <vector>
#include <string>
#include "ResourceList.h"
#include "UserList.h"
#include "Loan.h"

/**
 * @brief Describes the direction of a sorted list.
 */
enum class SortOrder {
    Ascending,  ///< A to Z  (default)
    Descending  ///< Z to A
};

/**
 * @brief Describes which field to sort a resource list by.
 */
enum class SortField {
    Title,  ///< Sort by resource title
    Author  ///< Sort by author name (meaningful for Books; empty string for others)
};

/**
 * @brief Top-level controller for the library management system.
 *
 * Owns the three core data structures: a ResourceList, a UserList,
 * and a vector of active Loans: and exposes all operations the REPL calls.
 *
 * Extended features added:
 *   - Sort available / loaned lists by title or author, ascending or descending
 *   - Keyword search across title, author, and conference acronym
 *   - Activity log that records every borrow and return event in order
 *   - Save the users-with-loans report to an external text file
 *
 * All user-facing output is delegated to Display so this class stays
 * focused purely on business logic.
 */
class LibrarySystem {
private:
    ResourceList resources; /// All resources loaded from file
    UserList users; /// All users loaded from file
    std::vector<Loan> loans; /// Currently active loans
    std::vector<std::string> activityLog; /// Chronological record of borrow/return events

    /**
     * @brief Appends a timestamped entry to the activity log.
     *
     * Called internally by borrowResource() and returnResource().
     *
     * @param entry  Human-readable description of the event.
     */
    void logActivity(const std::string& entry);

public:
    /**
     * @brief Loads resource and user data from their respective text files.
     */
    void loadData();

    // Core operations

    /**
     * @brief Attempts to issue a loan for the given user and resource.
     *
     * @param userID      Integer ID of the borrowing user.
     * @param resourceID  String ID of the resource (e.g. "B3").
     * @return true on success; false otherwise.
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

    // Listing & reports (extended with sort options)

    /**
     * @brief Lists all resources that are lendable and not currently on loan.
     *
     * @param order Ascending or Descending.
     * @param field Sort by Title or Author.
     */
    void listAvailableResources(SortOrder order = SortOrder::Ascending,
                                SortField field = SortField::Title) const;

    /**
     * @brief Reports every resource currently on loan and who has it.
     *
     * @param order  Ascending or Descending.
     * @param field  Sort by Title or Author.
     */
    void reportLoanedResources(SortOrder order = SortOrder::Ascending,
                               SortField field = SortField::Title) const;

    /**
     * @brief Reports every user who has at least one active loan.
     *
     * @param saveToFile  If true, also writes the report to "user_report.txt".
     */
    void reportUsersWithLoans(bool saveToFile = false) const;

    // Extended FEatures

    /**
     * @brief Case-insensitive keyword search across title, author, and acronym.
     *
     * Results are printed sorted alphabetically by title.
     *
     * @param keyword The search term.
     */
    void searchResources(const std::string& keyword) const;

    /**
     * @brief Prints the full activity log in chronological order.
     *
     * Each entry records whether it was a borrow or return, the resource
     * title, and the user name.
     */
    void displayActivityLog() const;
};

#endif //LIBRARY_SYS_LIBRARYSYSTEM_H