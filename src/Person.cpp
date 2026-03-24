//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "../include/Users/Person.h"

// ────────────────────────────────────────────────────────────────────────────
// Accessors
// ────────────────────────────────────────────────────────────────────────────

/**
 * @return The maximum number of resources this user is permitted to hold
 *         at any one time. Set by the subclass constructor.
 */
int Person::getBorrowLimit() const {
    return borrowLimit;
}

/**
 * @return The user's unique integer ID, assigned sequentially by UserList
 *         at load time.
 */
int Person::getID() const {
    return ID;
}

/**
 * @return The user's display name as read from the user file.
 */
std::string Person::getName() const {
    return name;
}

/**
 * @return The number of resources this user currently has on loan.
 *         Should never exceed borrowLimit under normal operation.
 */
int Person::getCurrentlyBorrowing() const {
    return currentlyBorrowing;
}

// ────────────────────────────────────────────────────────────────────────────
// Borrow count management
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Increments the borrowed resource count by one.
 *
 * Called by Loan::issueLoan() after all validation checks pass.
 * Not intended for direct use outside the loan management flow.
 */
void Person::incrementBorrowing() {
    currentlyBorrowing++;
}

/**
 * @brief Decrements the borrowed resource count by one.
 *
 * Called by Loan::returnLoan() when a resource is handed back.
 * Not intended for direct use outside the loan management flow.
 */
void Person::decrementBorrowing() {
    currentlyBorrowing--;
}