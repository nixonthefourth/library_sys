//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../../include/Logic/Loan.h"

// Constructor
Loan::Loan(Person* borrower, Resource* resource)
    : borrower(borrower), resource(resource) {}

// Issue a loan (borrow a resource)
bool Loan::issueLoan() {

    // Check if resource can be lent
    if (!resource->getLend()) {
        return false;
    }

    // Check if already borrowed
    if (resource->getBorrowed()) {
        return false;
    }

    // Check user limit
    if (borrower->getCurrentlyBorrowing() >= borrower->getBorrowLimit()) {
        return false;
    }

    // Apply loan
    resource->setBorrowed(true);
    borrower->incrementBorrowing();

    return true;
}

// Return a loan
bool Loan::returnLoan() {

    // If it's not borrowed, can't return
    if (!resource->getBorrowed()) {
        return false;
    }

    resource->setBorrowed(false);
    borrower->decrementBorrowing();

    return true;
}

// Getters
Person* Loan::getBorrower() const {
    return borrower;
}

Resource* Loan::getResource() const {
    return resource;
}