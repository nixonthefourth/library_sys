//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "../include/Resources/Resource.h"
#include <string>

/**
 *
 * @return Returns whether the resource can be lent
 */
bool Resource::getLend() const {
    return canLend;
}

/**
 *
 * @return Returns the ID of the resource
 */
std::string Resource::getID() const {
    return ID;
}

/**
 *
 * @return Returns whether the resource was borrowed
 */
bool Resource::getBorrowed() const {
    return isBorrowed;
}

/**
 *
 * @return Returns the title of the resource
 */
std::string Resource::getTitle() const {
    return title;
}

/**
 *
 * @param status Sets the resource's status on availibility
 */
void Resource::setBorrowed(bool status) {
    isBorrowed = status;
}