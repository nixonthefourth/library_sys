//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_CONFERENCE_H
#define LIBRARY_SYS_CONFERENCE_H

#include "Resource.h"
#include <string>

/**
 * @brief A conference proceedings resource — reference only, cannot be borrowed.
 *
 * Passes canLend = false to the Resource constructor so it is excluded from
 * the available-resources list and blocked by Loan::issueLoan().
 *
 * Each conference entry represents one specific year's proceedings identified
 * by its acronym (e.g. "CHI2025").  Multiple Conference objects share the same
 * full title but hold different acronyms, which is how the data file maps to objects.
 *
 * IDs are assigned by ResourceList with the prefix "C" (e.g. "C1", "C2").
 */
class Conference : public Resource {
private:
    std::string acronym;  ///< Short identifier for this edition (e.g. "CHI2025")

public:

    /**
     * @brief Constructs a Conference proceedings entry.
     *
     * @param ID Unique string identifier (e.g. "C4").
     * @param isBorrowed Initial borrowed state – false when loaded from file.
     * @param title Full conference name (e.g. "ACM Conference on Computer-Human Interaction").
     * @param acronym Year-specific short code (e.g. "CHI2025").
     */
    Conference(const std::string& ID,
               bool isBorrowed,
               const std::string& title,
               const std::string& acronym)
        : Resource(false, ID, isBorrowed, title), acronym(acronym) {}

    /**
     * @return The year-specific acronym for this conference edition.
     */
    std::string getTitleAcronym() const {
        return acronym;
    }
};

#endif //LIBRARY_SYS_CONFERENCE_H