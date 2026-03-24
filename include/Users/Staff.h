//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_STAFF_H
#define LIBRARY_SYS_STAFF_H

#include "Users/Person.h"
#include <string>

/**
 * @brief A university staff member – may hold up to 2 resources at a time.
 *
 * The higher borrow limit reflects staff privileges and is enforced by
 * passing 2 to Person's constructor.
 * Type code in A2UserList.txt: '2'.
 */
class Staff : public Person {
public:

    /**
     * @brief Constructs a Staff member.
     *
     * @param ID Unique integer ID assigned sequentially by UserList.
     * @param name Display name read from the user file.
     */
    Staff(int ID, const std::string& name)
        : Person(2, ID, name, 0) {}
};

#endif //LIBRARY_SYS_STAFF_H