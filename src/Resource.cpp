//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "../include/Resources/Resource.h"
#include <string>

/**
 * @return Whether this resource type allows lending.
 *         Set once at construction by the subclass.
 */
bool Resource::getLend() const {
    return canLend;
}

/**
 * @return The unique string ID (e.g. "B3", "J1", "C7").
 */
std::string Resource::getID() const {
    return ID;
}

/**
 * @return True while the resource is on loan to a user.
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

/**
 * @return The author name for Books; empty string for Journals and Conferences.
 */
std::string Resource::getAuthor() const {
    return author;
}

/**
 * @brief Updates the availability flag on this resource.
 *
 * Called by Loan::issueLoan() (true) and Loan::returnLoan() (false).
 * Not intended for direct use outside the loan management flow.
 *
 * @param status True to mark the resource as borrowed; false to mark available.
 */
void Resource::setBorrowed(bool status) {
    isBorrowed = status;
}