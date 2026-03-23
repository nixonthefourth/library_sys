//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_BOOK_H
#define LIBRARY_SYS_BOOK_H

#include "Resource.h"
#include <string>

/**
 * Inherits from the parental class Resources and defines a class-specific constructor
 */
class Book : public Resource {
public:
    Book(const std::string& ID,
        bool isBorrowed,
        const std::string& title) : Resource(true, ID, isBorrowed, title) {}
};

#endif //LIBRARY_SYS_BOOK_H