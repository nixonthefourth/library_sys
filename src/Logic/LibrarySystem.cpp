//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "Logic/LibrarySystem.h"
#include "Resources/Conference.h"
#include "Display.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <chrono>
#include <ctime>

// ────────────────────────────────────────────────────────────────────────────
// Internal helpers
// ────────────────────────────────────────────────────────────────────────────

namespace {

    /**
     * @brief Returns the current wall-clock time formatted as HH:MM:SS.
     *
     * Used to timestamp activity log entries.
     */
    std::string timestamp() {
        auto now    = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        char buf[10];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
        return std::string(buf);
    }

    /**
     * @brief Comparator for sorting Resource pointers by title, ascending.
     */
    bool byTitleAsc(Resource* a, Resource* b) {
        return a->getTitle() < b->getTitle();
    }

    /**
     * @brief Comparator for sorting Resource pointers by title, descending.
     */
    bool byTitleDesc(Resource* a, Resource* b) {
        return a->getTitle() > b->getTitle();
    }

    /**
     * @brief Comparator for sorting Resource pointers by author, ascending.
     *
     * Falls back to title comparison when both authors are equal (or empty),
     * so the output is deterministic for Journals and Conferences.
     */
    bool byAuthorAsc(Resource* a, Resource* b) {
        if (a->getAuthor() != b->getAuthor())
            return a->getAuthor() < b->getAuthor();
        return a->getTitle() < b->getTitle();
    }

    /**
     * @brief Comparator for sorting Resource pointers by author, descending.
     */
    bool byAuthorDesc(Resource* a, Resource* b) {
        if (a->getAuthor() != b->getAuthor())
            return a->getAuthor() > b->getAuthor();
        return a->getTitle() > b->getTitle();
    }

    /**
     * @brief Selects and applies the correct comparator, then returns the sorted copy.
     *
     * @param vec The vector of Resource* to sort (taken by value — caller's copy).
     * @param order Ascending or Descending.
     * @param field Title or Author.
     * @return The sorted vector.
     */
    std::vector<Resource*> sorted(std::vector<Resource*> vec,
                                  SortOrder order,
                                  SortField field) {
        if (field == SortField::Title) {
            std::sort(vec.begin(), vec.end(),
                order == SortOrder::Ascending ? byTitleAsc : byTitleDesc);
        } else {
            std::sort(vec.begin(), vec.end(),
                order == SortOrder::Ascending ? byAuthorAsc : byAuthorDesc);
        }
        return vec;
    }

}

// ────────────────────────────────────────────────────────────────────────────
// Activity log
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Prepends a timestamp and appends the entry to the log vector.
 *
 * Format: "[HH:MM:SS]  <entry text>"
 *
 * @param entry  Human-readable description of the event.
 */
void LibrarySystem::logActivity(const std::string& entry) {
    activityLog.push_back("[" + timestamp() + "]  " + entry);
}

// ────────────────────────────────────────────────────────────────────────────
// Data loading
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Loads resource and user data from their respective text files.
 */
void LibrarySystem::loadData() {
    std::cout << Display::DIM << "  Loading resources..." << Display::RESET << "\n";
    resources.loadFromFile("../docs/A2ResourceList.txt");

    std::cout << Display::DIM << "  Loading users..." << Display::RESET << "\n";
    users.loadFromFile("../docs/A2UserList.txt");

    std::cout << "\n";
}

// ────────────────────────────────────────────────────────────────────────────
// Core — Borrowing
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Looks up both entities by ID, constructs a Loan, and calls issueLoan().
 *
 * On success the loan is stored and a log entry is appended.
 * On failure the reason is surfaced specifically through Display::error().
 *
 * @param userID Integer ID of the borrowing user.
 * @param resourceID String ID of the target resource.
 * @return true if the loan was created; false otherwise.
 */
bool LibrarySystem::borrowResource(int userID, const std::string& resourceID) {
    Person*   user     = users.findByID(userID);
    Resource* resource = resources.findByID(resourceID);

    if (!user || !resource) {
        Display::error("User or resource not found — check the IDs and try again.");
        return false;
    }

    Loan loan(user, resource);

    if (loan.issueLoan()) {
        loans.push_back(loan);
        logActivity("BORROW  " + resource->getTitle() + "  →  " + user->getName());
        Display::success("Loan created — " + resource->getTitle()
                         + " is now checked out to " + user->getName() + ".");
        return true;
    }

    // Surface the specific failure reason
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
// Core — Returning
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Iterates the loans vector looking for a matching (userID, resourceID) pair.
 *
 * On a match, returnLoan() is called, the loan is erased, and a log entry
 * is appended.
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
            std::string name  = it->getBorrower()->getName();

            it->returnLoan();
            loans.erase(it);

            logActivity("RETURN  " + title + "  ←  " + name);
            Display::success(title + " returned successfully.");
            return true;
        }
    }

    Display::error("No matching loan found — verify the user ID and resource ID.");
    return false;
}

// ────────────────────────────────────────────────────────────────────────────
// Core — Listing & reports
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Lists every resource that is lendable and not currently borrowed.
 *
 * The result set is filtered first, then sorted according to the caller's
 * chosen order and field before printing.
 *
 * @param order Ascending or Descending.
 * @param field Title or Author.
 */
void LibrarySystem::listAvailableResources(SortOrder order, SortField field) const {
    Display::heading("AVAILABLE RESOURCES");

    // Build filtered list first, then sort
    std::vector<Resource*> available;
    for (auto r : resources.getResources()) {
        if (!r->getBorrowed() && r->getLend()) {
            available.push_back(r);
        }
    }

    if (available.empty()) {
        Display::empty("available resources");
        return;
    }

    for (auto r : sorted(available, order, field)) {
        // Show author in brackets if present, so sort-by-author is clearly visible
        if (!r->getAuthor().empty()) {
            Display::row(r->getID(), r->getTitle() + "  " +
                         std::string(Display::DIM) + "[" + r->getAuthor() + "]" +
                         std::string(Display::RESET));
        } else {
            Display::row(r->getID(), r->getTitle());
        }
    }
}

/**
 * @brief Reports every resource currently on loan and who has it, sorted as requested.
 *
 * @param order Ascending or Descending.
 * @param field Title or Author.
 */
void LibrarySystem::reportLoanedResources(SortOrder order, SortField field) const {
    Display::heading("LOAN REPORT");

    if (loans.empty()) {
        Display::empty("active loans");
        return;
    }

    // Collect resource pointers from the loans vector then sort
    std::vector<Resource*> loaned;
    for (const auto& loan : loans) {
        loaned.push_back(loan.getResource());
    }

    // Build a map resource→borrower for printing after sort
    // (we need the borrower name alongside the sorted resource)
    std::vector<std::pair<Resource*, Person*>> pairs;
    for (const auto& loan : loans) {
        pairs.push_back({ loan.getResource(), loan.getBorrower() });
    }

    // Sort the pairs by the resource field
    if (field == SortField::Title) {
        std::sort(pairs.begin(), pairs.end(),
            [&](const auto& a, const auto& b) {
                return order == SortOrder::Ascending
                    ? a.first->getTitle() < b.first->getTitle()
                    : a.first->getTitle() > b.first->getTitle();
            });
    } else {
        std::sort(pairs.begin(), pairs.end(),
            [&](const auto& a, const auto& b) {
                const std::string& aa = a.first->getAuthor();
                const std::string& ba = b.first->getAuthor();
                if (aa != ba)
                    return order == SortOrder::Ascending ? aa < ba : aa > ba;
                return order == SortOrder::Ascending
                    ? a.first->getTitle() < b.first->getTitle()
                    : a.first->getTitle() > b.first->getTitle();
            });
    }

    for (const auto& p : pairs) {
        Display::loanRow(p.first->getTitle(), p.second->getName());
    }
}

/**
 * @brief Reports every user who has at least one active loan.
 *
 * Uses a set to deduplicate – each user appears at most once.
 * If saveToFile is true, the same report is written to "user_report.txt".
 *
 * @param saveToFile If true, also writes the report to disk.
 */
void LibrarySystem::reportUsersWithLoans(bool saveToFile) const {
    Display::heading("USERS WITH ACTIVE LOANS");

    if (loans.empty()) {
        Display::empty("users with loans");
        return;
    }

    std::set<int> seen;
    std::vector<std::pair<int, std::string>> rows; // <ID, name> for file writing

    for (const auto& loan : loans) {
        Person* user = loan.getBorrower();

        // insert() returns false when the key is already present
        if (seen.insert(user->getID()).second) {
            Display::row(std::to_string(user->getID()), user->getName());
            rows.push_back({ user->getID(), user->getName() });
        }
    }

    // ---- File export ----
    if (saveToFile) {
        std::ofstream out("user_report.txt");

        if (!out.is_open()) {
            Display::error("Could not open user_report.txt for writing.");
            return;
        }

        out << "USERS WITH ACTIVE LOANS\n";
        out << "========================\n";
        for (const auto& row : rows) {
            out << "[" << row.first << "]  " << row.second << "\n";
        }
        out.close();

        Display::success("Report saved to user_report.txt.");
    }
}

// ────────────────────────────────────────────────────────────────────────────
// Extended — Search
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Delegates to ResourceList::searchByKeyword and prints the results.
 *
 * Results come back pre-sorted alphabetically by title from the search method.
 * The author is shown in brackets when present so searches that matched on
 * author are clearly visible.
 *
 * @param keyword The search term (case-insensitive).
 */
void LibrarySystem::searchResources(const std::string& keyword) const {
    Display::heading("SEARCH RESULTS:  \"" + keyword + "\"");

    std::vector<Resource*> results = resources.searchByKeyword(keyword);

    if (results.empty()) {
        Display::empty("results for \"" + keyword + "\"");
        return;
    }

    for (auto r : results) {
        std::string label = r->getTitle();

        if (!r->getAuthor().empty()) {
            label += "  " + std::string(Display::DIM) +
                     "[" + r->getAuthor() + "]" + Display::RESET;
        }

        // Append the acronym for Conference resources
        if (auto* conf = dynamic_cast<Conference*>(r)) {
            label += "  " + std::string(Display::GREY) +
                     conf->getTitleAcronym() + Display::RESET;
        }

        // Tag borrowed resources so staff can see at a glance
        if (r->getBorrowed()) {
            label += "  " + std::string(Display::YELLOW) + "(on loan)" + Display::RESET;
        }

        Display::row(r->getID(), label);
    }
}

// ────────────────────────────────────────────────────────────────────────────
// Activity log
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Prints the full activity log in the order events were recorded.
 *
 * Each entry was appended by logActivity() at the time of the event and
 * carries an HH:MM:SS timestamp.
 */
void LibrarySystem::displayActivityLog() const {
    Display::heading("ACTIVITY LOG");

    if (activityLog.empty()) {
        Display::empty("activity to show: no loans have been made yet");
        return;
    }

    for (size_t i = 0; i < activityLog.size(); ++i) {
        // Print entry number as the "ID" badge and the log string as the label
        Display::row(std::to_string(i + 1), activityLog[i]);
    }
}