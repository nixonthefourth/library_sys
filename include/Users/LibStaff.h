//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_LIBRARYSTAFF_H
#define LIBRARY_SYS_LIBRARYSTAFF_H

#include "Users/Person.h"
#include <string>

/**
 * @brief A library staff member – cannot borrow any resources.
 *
 * The borrow limit of 0 ensures issueLoan() will always reject a borrow
 * attempt for this user type. Library staff exist in the system to
 * process loans on behalf of others, not to borrow themselves.
 * Type code in A2UserList.txt: '3'.
 */
class LibStaff : public Person {
public:

    /**
     * @brief Constructs a LibStaff member.
     *
     * @param ID Unique integer ID assigned sequentially by UserList.
     * @param name Display name read from the user file.
     */
    LibStaff(int ID, const std::string& name)
        : Person(0, ID, name, 0) {}
};

#endif //LIBRARY_SYS_LIBRARYSTAFF_H