//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Person.h"

/**
 *
 * @return Returns the borrow limit of the user
 */
int Person::getBorrowLimit() const {
    return borrowLimit;
}

/**
 *
 * @return Returns user's ID
 */
int Person::getID() const {
    return ID;
}

/**
 *
 * @return Returns username
 */
std::string Person::getName() const {
    return name;
}
