//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_JOURNAL_H
#define LIBRARY_SYS_JOURNAL_H

#include "Resource.h"
#include <string>

/**
 * @brief An academic journal that can be borrowed.
 *
 * Structurally identical to Book in terms of lending rules: canLend = true.
 * Kept as a separate subclass so the type is preserved in memory and can be
 * distinguished (e.g. for future reporting or display purposes).
 * IDs are assigned by ResourceList with the prefix "J" (e.g. "J1", "J2").
 */
class Journal : public Resource {
public:

    /**
     * @brief Constructs a Journal.
     *
     * @param ID Unique string identifier (e.g. "J1").
     * @param isBorrowed Initial borrowed state – false when loaded from file.
     * @param title Human-readable title.
     */
    Journal(const std::string& ID,
            bool isBorrowed,
            const std::string& title)
        : Resource(true, ID, isBorrowed, title) {}
};

#endif //LIBRARY_SYS_JOURNAL_H