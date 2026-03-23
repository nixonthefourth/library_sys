//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_LOAN_H
#define LIBRARY_SYS_LOAN_H

#include "Person.h"
#include "Resource.h"

class Loan {
private:
    Person* borrower;
    Resource* resource;

public:
    Loan(Person* borrower, Resource* resource);

    bool issueLoan();     // borrow
    bool returnLoan();    // return

    Person* getBorrower() const;
    Resource* getResource() const;
};

#endif