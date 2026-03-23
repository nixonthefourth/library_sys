//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_CONFERENCE_H
#define LIBRARY_SYS_CONFERENCE_H

#include <string>
#include "Resource.h"

class Conference : public Resource {
private: // Private, since applies only to conference
    std::string acronym;

public:
    // Public constructor
    Conference(int ID, bool isBorrowed, std::string title, std::string acronym)
        : Resource(false, ID, isBorrowed, title),
          acronym(acronym) {}

    // Public accessor
    std::string getTitleAcronym() const {
        return acronym;
    }
};

#endif //LIBRARY_SYS_CONFERENCE_H