//
// Created by Mykyta Khomiakov on 23/03/2026.
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
 * @return 0 on clean exit.
 */
int main() {

    LibrarySystem system;

    // Animate the banner before loading so there is something on screen
    Display::banner();

    system.loadData();

    int choice = -1;

    while (true) {

        Display::menu();

        // Prompt for menu choice — reuse the styled prompt
        choice = Display::promptInt("choice");

        // Flush any leftover newline so subsequent getlines behave
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            Display::typewriteLine("\n  Goodbye.", 25);
            break;
        }

        // ---- 1. Borrow ----
        if (choice == 1) {
            int         userID     = Display::promptInt("user ID");
            std::string resourceID = Display::promptStr("resource ID");
            system.borrowResource(userID, resourceID);
        }

        // ---- 2. Return ----
        else if (choice == 2) {
            int         userID     = Display::promptInt("user ID");
            std::string resourceID = Display::promptStr("resource ID");
            system.returnResource(userID, resourceID);
        }

        // ---- 3. List available ----
        else if (choice == 3) {
            system.listAvailableResources();
        }

        // ---- 4. Loan report ----
        else if (choice == 4) {
            system.reportLoanedResources();
        }

        // ---- 5. User report ----
        else if (choice == 5) {
            system.reportUsersWithLoans();
        }

        else {
            Display::error("Unknown option — please enter a number from the menu.");
        }
    }

    return 0;
}