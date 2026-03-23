//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_USERLIST_H
#define LIBRARY_SYS_USERLIST_H

#include <vector>
#include <string>
#include "Users/Person.h"

class UserList {
private:
    std::vector<Person*> users;

public:
    void loadFromFile(const std::string& filename);

    std::vector<Person*> getUsers() const;

    Person* findByID(int id) const;

    ~UserList(); // cleanup
};

#endif