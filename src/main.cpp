//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "Logic/LibrarySystem.h"
#include "Display.h"
#include <iostream>
#include <limits>

/**
 * @brief Application entry point.
 *
 * Boots the LibrarySystem, plays the startup banner, then runs the main
 * menu loop until the user chooses to exit.
 *
 * Options 3 and 4 (list available / loan report) ask for sort preferences
 * before delegating to LibrarySystem. Option 5 (user report) asks whether
 * the output should also be saved to a file. Options 6 and 7 are the
 * extended keyword search and activity log features respectively.
 *
 * @return 0 on clean exit.
 */
int main() {
    setlocale(LC_ALL, ".utf8");

    LibrarySystem system;

    // Animate the banner before loading so the screen is not blank on launch
    Display::banner();

    system.loadData();

    int choice = -1;

    while (true) {

        Display::menu();

        choice = Display::promptInt("choice");

        // Flush the leftover newline so subsequent reads behave correctly
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            Display::typewriteLine("\n  Goodbye.", 25);
            break;
        }

        // ---- 1. Borrow ----
        if (choice == 1) {
            int userID = Display::promptInt("user ID");
            std::string resID = Display::promptStr("resource ID");
            system.borrowResource(userID, resID);
        }

        // ---- 2. Return ----
        else if (choice == 2) {
            int userID = Display::promptInt("user ID");
            std::string resID = Display::promptStr("resource ID");
            system.returnResource(userID, resID);
        }

        // ---- 3. List available (with sort) ----
        else if (choice == 3) {
            char order = 'a', field = 't';
            Display::sortMenu(order, field);

            system.listAvailableResources(
                order == 'd' ? SortOrder::Descending : SortOrder::Ascending,
                field == 'a' ? SortField::Author : SortField::Title
            );
        }

        // ---- 4. Loan report (with sort) ----
        else if (choice == 4) {
            char order = 'a', field = 't';
            Display::sortMenu(order, field);

            system.reportLoanedResources(
                order == 'd' ? SortOrder::Descending : SortOrder::Ascending,
                field == 'a' ? SortField::Author : SortField::Title
            );
        }

        // ---- 5. User report (optional file save) ----
        else if (choice == 5) {
            bool save = Display::saveReportPrompt();
            system.reportUsersWithLoans(save);
        }

        // ---- 6. Search ----
        else if (choice == 6) {
            std::string keyword = Display::promptStr("search keyword");
            system.searchResources(keyword);
        }

        // ---- 7. Activity log ----
        else if (choice == 7) {
            system.displayActivityLog();
        }

        else {
            Display::error("Unknown option – please enter a number from the menu.");
        }
    }

    return 0;
}