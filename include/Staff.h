//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_STAFF_H
#define LIBRARY_SYS_STAFF_H

#include <string>
#include "Person.h"

/**
 * @brief Inherits from parental class Person. Sets staff member's resource borrow limit as 2.
 */
class Staff : public Person {
private:
    int resourcesBorrowed;

public:
    Staff(int ID,
        std::string name,
        int resourcesBorrowed) : Person(2, ID, name), resourcesBorrowed(resourcesBorrowed) {}

    // Public accessors
    /**
     *
     * @return Returns the current number of borrowed items
     */
    int getResourcesBorrowed() const {
        return resourcesBorrowed;
    }

    /**
     *
     * @param newResourcesBorrowed Sets new resource borrow number
     */
    void setResourcesBorrowed(int newResourcesBorrowed) { resourcesBorrowed = newResourcesBorrowed; }
};

#endif //LIBRARY_SYS_STAFF_H