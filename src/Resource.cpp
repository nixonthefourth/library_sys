//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../include/Resources/Resource.h"
#include <string>

// ────────────────────────────────────────────────────────────────────────────
// Accessors
// ────────────────────────────────────────────────────────────────────────────

/**
 * @return Whether this resource type allows lending.
 *         Set once at construction by the subclass — true for Book/Journal,
 *         false for Conference.
 */
bool Resource::getLend() const {
    return canLend;
}

/**
 * @return The unique string ID of this resource (e.g. "B3", "J1", "C7").
 *         Assigned by ResourceList at load time.
 */
std::string Resource::getID() const {
    return ID;
}

/**
 * @return True while the resource is on loan to a user; false when available.
 */
bool Resource::getBorrowed() const {
    return isBorrowed;
}

/**
 * @return The human-readable title of this resource.
 */
std::string Resource::getTitle() const {
    return title;
}

// ────────────────────────────────────────────────────────────────────────────
// Mutator
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Updates the availability flag on this resource.
 *
 * Called by Loan::issueLoan() (true) and Loan::returnLoan() (false).
 * Not intended for direct use outside the loan management flow.
 *
 * @param status  True to mark the resource as borrowed; false to mark it
 *                as available.
 */
void Resource::setBorrowed(bool status) {
    isBorrowed = status;
}