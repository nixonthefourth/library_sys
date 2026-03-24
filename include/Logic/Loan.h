//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_LOAN_H
#define LIBRARY_SYS_LOAN_H

#include "../Users/Person.h"
#include "../Resources/Resource.h"

/**
 * @brief Associates one Person with one Resource for the duration of a borrowing period.
 *
 * A Loan does not own the objects it points to — both pointers must remain
 * valid for the lifetime of the Loan.  The LibrarySystem is responsible
 * for ensuring this by storing resources and users in long-lived containers.
 */
class Loan {
private:
    Person* borrower;  /// Non-owning pointer to the user who borrowed the resource
    Resource* resource;  /// Non-owning pointer to the borrowed resource

public:

    /**
     * @brief Constructs a Loan between a borrower and a resource.
     *
     * Does not modify either object – call issueLoan() to apply the loan.
     *
     * @param borrower Pointer to the Person borrowing the resource.
     * @param resource Pointer to the Resource being borrowed.
     */
    Loan(Person* borrower, Resource* resource);

    /**
     * @brief Validates and applies the loan.
     *
     * Checks that: (1) the resource allows lending, (2) it is not already
     * borrowed, and (3) the borrower has not hit their borrow limit.
     * On success, marks the resource as borrowed and increments the
     * borrower's count.
     *
     * @return true if the loan was issued; false if any check failed.
     */
    bool issueLoan();

    /**
     * @brief Reverses a loan, making the resource available again.
     *
     * Marks the resource as not borrowed and decrements the borrower's count.
     *
     * @return true if the return was applied; false if the resource was not
     *         marked as borrowed (shouldn't happen under normal flow).
     */
    bool returnLoan();

    /**
     * @return Non-owning pointer to the Person who holds this loan.
     */
    Person* getBorrower() const;

    /**
     * @return Non-owning pointer to the Resource covered by this loan.
     */
    Resource* getResource() const;
};

#endif //LIBRARY_SYS_LOAN_H