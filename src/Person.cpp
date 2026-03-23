//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../include/Users/Person.h"

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

/**
 *
 * @return Returns the number of currently borrowed resources
 */
int Person::getCurrentlyBorrowing() const {
    return currentlyBorrowing;
}

/**
 * Increments the number of borrowed elements
 */
void Person::incrementBorrowing() {
    currentlyBorrowing++;
}

/**
 * Decrements the number of borrowed elements
 */
void Person::decrementBorrowing() {
    currentlyBorrowing--;
}
