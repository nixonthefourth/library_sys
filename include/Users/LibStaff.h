//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_LIBRARYSTAFF_H
#define LIBRARY_SYS_LIBRARYSTAFF_H

#include <string>
#include "Users/Person.h"

/**
 * @brief Inherits from parental class Person. Sets library staff's resource borrow limit as 1.
 */
class LibStaff : public Person {
public:
    LibStaff(int ID, std::string name) : Person(0, ID, name, 0) {}
};

#endif //LIBRARY_SYS_LIBRARYSTAFF_H