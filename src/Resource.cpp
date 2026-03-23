//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Resource.h"
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
int Resource::getID() const {
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
