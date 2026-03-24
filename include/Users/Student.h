//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_STUDENT_H
#define LIBRARY_SYS_STUDENT_H

#include "Users/Person.h"
#include <string>

/**
 * @brief A student user – may hold up to 1 resource at a time.
 *
 * The borrow limit of 1 is enforced by passing it to Person's constructor;
 * no additional logic is needed here.
 * Type code in A2UserList.txt: '1'.
 */
class Student : public Person {
public:

    /**
     * @brief Constructs a Student.
     *
     * @param ID Unique integer ID assigned sequentially by UserList.
     * @param name Display name read from the user file.
     */
    Student(int ID, const std::string& name)
        : Person(1, ID, name, 0) {}
};

#endif //LIBRARY_SYS_STUDENT_H