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
public:
    Staff(int ID,
        std::string name) : Person(2, ID, name, 0){}
};

#endif //LIBRARY_SYS_STAFF_H