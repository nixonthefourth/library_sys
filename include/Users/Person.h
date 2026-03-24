//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_PERSON_H
#define LIBRARY_SYS_PERSON_H

#include <string>

/**
 * @brief Base class for all users in the library system.
 *
 * Holds the fields common to every user type – ID, name, borrow limit,
 * and a running count of currently borrowed resources. Concrete subclasses
 * (Student, Staff, LibStaff) set the limit in their constructors.
 *
 * All accessors are virtual so subclasses can override them if needed,
 * and so the hierarchy is safe for polymorphic use through Person*.
 */
class Person {
protected:
    int borrowLimit; /// Maximum number of resources this user may hold
    int ID; /// Unique integer identifier assigned at load time
    std::string name; /// Display name as read from the user file
    int currentlyBorrowing; ///Running count of resources currently on loan

public:

    /**
     * @brief Constructs a Person with all core fields.
     *
     * @param borrowLimit Passed by value: int is cheaper to copy than reference.
     * @param ID Passed by value: int is cheaper to copy than reference.
     * @param name Passed by const-ref: avoids copying the string.
     * @param currentlyBorrowing Passed by value: int is cheaper to copy than reference.
     */
    Person(int borrowLimit,
           int ID,
           const std::string& name,
           int currentlyBorrowing)
        : borrowLimit(borrowLimit), ID(ID), name(name),
          currentlyBorrowing(currentlyBorrowing) {}

    /**
     * @return The maximum number of resources this user is allowed to borrow.
     */
    virtual int getBorrowLimit() const;

    /**
     * @return The user's unique integer ID.
     */
    virtual int getID() const;

    /**
     * @return The user's display name.
     */
    virtual std::string getName() const;

    /**
     * @return How many resources this user currently has on loan.
     */
    int getCurrentlyBorrowing() const;

    /**
     * @brief Increments the borrowed count when a new loan is issued.
     *
     * Called by Loan::issueLoan() – not intended for direct use elsewhere.
     */
    void incrementBorrowing();

    /**
     * @brief Decrements the borrowed count when a loan is returned.
     *
     * Called by Loan::returnLoan() – not intended for direct use elsewhere.
     */
    void decrementBorrowing();

    /// Virtual destructor – required for safe polymorphic deletion via Person*.
    virtual ~Person() = default;
};

#endif //LIBRARY_SYS_PERSON_H