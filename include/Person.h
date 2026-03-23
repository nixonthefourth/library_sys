//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_PERSON_H
#define LIBRARY_SYS_PERSON_H
#include <string>

/**
 * @brief Class of the person in the library system.
 *
 * Includes the limit of the resources person can borrow, their ID and their systemic name.
 */
class Person {
protected: // Private Variables
    int borrowLimit;
    int ID;
    std::string name;

public: // Public Accessors
    // Constructor
    Person(int borrowLimit, // Passed by value, since it's cheaper to copy than reference
           int ID, // Passed by value, since it's cheaper to copy than reference
           const std::string &name // Passed by reference, since referencing long strings is cheaper than copying
           ) : borrowLimit(borrowLimit), ID(ID), name(name) {};

    // Getters

    // Setters are disabled since, those are set initially in an inherited constructor and later on after file parsing
    virtual int getBorrowLimit() const;
    virtual int getID() const;
    virtual std::string getName() const;

    // Virtual destructor
    virtual ~Person() = default;
};

#endif //LIBRARY_SYS_PERSON_H