//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_STUDENT_H
#define LIBRARY_SYS_STUDENT_H
#include <string>
#include "Person.h"

/**
 * @brief Inherits from parental class Person. Sets student's resource borrow limit as 1.
 */
class Student : public Person {
private:
    int resourcesBorrowed;
public:
    Student(int ID,
        const std::string &name,
        int resourcesBorrowed)
        : Person(1, ID, name),
        resourcesBorrowed(resourcesBorrowed) {} // Students can borrow up to 1 resource

    // Public Accessors
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

#endif //LIBRARY_SYS_STUDENT_H