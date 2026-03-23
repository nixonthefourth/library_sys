//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_STUDENT_H
#define LIBRARY_SYS_STUDENT_H
#include <string>
#include "../Person.h"

/**
 * @brief Inherits from parental class Person. Sets student's resource borrow limit as 1.
 */
class Student : public Person {
public:
    Student(int ID,
        const std::string &name)
        : Person(1, ID, name, 0) {} // Students can borrow up to 1 resource
};

#endif //LIBRARY_SYS_STUDENT_H