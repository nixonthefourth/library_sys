//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_LIBRARYSYSTEM_H
#define LIBRARY_SYS_LIBRARYSYSTEM_H

#include <vector>
#include "ResourceList.h"
#include "UserList.h"
#include "Loan.h"

class LibrarySystem {
private:
    ResourceList resources;
    UserList users;
    std::vector<Loan> loans;

public:
    void loadData();

    bool borrowResource(int userID, const std::string& resourceID);
    bool returnResource(int userID, const std::string& resourceID);

    void listAvailableResources() const;
    void reportLoanedResources() const;
    void reportUsersWithLoans() const;
};

#endif