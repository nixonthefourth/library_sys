//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../../include/Logic/Loan.h"

// ────────────────────────────────────────────────────────────────────────────
// Constructor
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Stores the borrower and resource pointers.
 *
 * Does not modify either object — issueLoan() must be called separately
 * to actually apply the loan.  Both pointers are non-owning; the caller
 * (LibrarySystem) is responsible for keeping them valid.
 *
 * @param borrower  Pointer to the Person requesting the resource.
 * @param resource  Pointer to the Resource being requested.
 */
Loan::Loan(Person* borrower, Resource* resource)
    : borrower(borrower), resource(resource) {}

// ────────────────────────────────────────────────────────────────────────────
// Loan lifecycle
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Validates all preconditions and applies the loan if they pass.
 *
 * Three checks are performed in order:
 *   1. The resource must allow lending (canLend == true).
 *   2. The resource must not already be on loan (isBorrowed == false).
 *   3. The borrower must be below their borrow limit.
 *
 * If all checks pass, the resource is marked borrowed and the borrower's
 * count is incremented.
 *
 * @return true if the loan was issued; false if any check failed.
 */
bool Loan::issueLoan() {

    // Checkpoint 1 – resource type permits lending
    if (!resource->getLend()) {
        return false;
    }

    // Checkpoint 2 – resource is currently available
    if (resource->getBorrowed()) {
        return false;
    }

    // Checkpoint 3 – borrower has capacity for another resource
    if (borrower->getCurrentlyBorrowing() >= borrower->getBorrowLimit()) {
        return false;
    }

    // All checks passed – apply the loan
    resource->setBorrowed(true);
    borrower->incrementBorrowing();

    return true;
}

/**
 * @brief Reverses a loan, returning the resource to the available pool.
 *
 * Guards against returning a resource that was never marked as borrowed,
 * which would indicate a logic error elsewhere in the system.
 *
 * @return true if the return was applied; false if the resource was not
 *         flagged as borrowed.
 */
bool Loan::returnLoan() {

    // Guard – shouldn't happen under normal flow, but defensive is good
    if (!resource->getBorrowed()) {
        return false;
    }

    resource->setBorrowed(false);
    borrower->decrementBorrowing();

    return true;
}

// ────────────────────────────────────────────────────────────────────────────
// Accessors
// ────────────────────────────────────────────────────────────────────────────

/**
 * @return Non-owning pointer to the Person who holds this loan.
 */
Person* Loan::getBorrower() const {
    return borrower;
}

/**
 * @return Non-owning pointer to the Resource covered by this loan.
 */
Resource* Loan::getResource() const {
    return resource;
}