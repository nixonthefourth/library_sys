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
 * Passes canLend = true to the Resource constructor so books appear in
 * the available-resources list and can be issued via Loan::issueLoan().
 *
 * Books are the only resource type that carry an author field; the value
 * is forwarded to Resource and exposed via getAuthor().  This is used by
 * the sort-by-author and keyword-search features.
 *
 * IDs are assigned by ResourceList with the prefix "B" (e.g. "B1", "B2").
 */
class Book : public Resource {
public:

    /**
     * @brief Constructs a Book.
     *
     * @param ID Unique string identifier (e.g. "B3").
     * @param isBorrowed Initial borrowed state — false when loaded from file.
     * @param title Human-readable title.
     * @param author Author name as read from the resource file.
     */
    Book(const std::string& ID,
         bool isBorrowed,
         const std::string& title,
         const std::string& author)
        : Resource(true, ID, isBorrowed, title, author) {}
};

#endif //LIBRARY_SYS_BOOK_H