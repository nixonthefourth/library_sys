//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_JOURNAL_H
#define LIBRARY_SYS_JOURNAL_H

#include <string>
#include "Resource.h"

/**
 * Inherits from the parental class Resources and defines a class-specific constructor
 */
class Journal : public Resource {
public:
    Journal(const std::string& ID,
        bool isBorrowed,
        const std::string& title) : Resource(true, ID, isBorrowed, title) {}
};

#endif //LIBRARY_SYS_JOURNAL_H