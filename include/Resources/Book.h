//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_BOOK_H
#define LIBRARY_SYS_BOOK_H

#include "Resource.h"
#include <string>

/**
 * @brief A physical or digital book that can be borrowed.
 *
 * Passes canLend = true to the Resource constructor, so books appear in
 * the available-resources list and can be issued via Loan::issueLoan().
 * IDs are assigned by ResourceList with the prefix "B" (e.g. "B1", "B2").
 */
class Book : public Resource {
public:

    /**
     * @brief Constructs a Book.
     *
     * @param ID Unique string identifier (e.g. "B3").
     * @param isBorrowed Initial borrowed state – false when loaded from file.
     * @param title User-readable title.
     */
    Book(const std::string& ID,
         bool isBorrowed,
         const std::string& title)
        : Resource(true, ID, isBorrowed, title) {}
};

#endif //LIBRARY_SYS_BOOK_H