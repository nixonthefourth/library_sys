//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Logic/UserList.h"
#include "Users/Student.h"
#include "Users/Staff.h"
#include "Users/LibStaff.h"

#include <fstream>
#include <iostream>

void UserList::loadFromFile(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open user file\n";
        return;
    }

    std::string line;
    int idCounter = 1;

    while (std::getline(file, line)) {

        // Strip Windows-style carriage return if present
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        // First char = type
        char type = line[0];

        // Rest = name
        std::string name = line.substr(1);

        Person* user = nullptr;

        if (type == '1') {
            user = new Student(idCounter, name);
        }
        else if (type == '2') {
            user = new Staff(idCounter, name);
        }
        else if (type == '3') {
            user = new LibStaff(idCounter, name);
        }

        if (user != nullptr) {
            users.push_back(user);
            idCounter++;
        }
    }

    std::cout << "Loaded users: " << users.size() << "\n";
    file.close();
}

// Utensils
std::vector<Person*> UserList::getUsers() const {
    return users;
}

Person* UserList::findByID(int id) const {
    for (auto user : users) {
        if (user->getID() == id) {
            return user;
        }
    }
    return nullptr;
}

// Destructor
UserList::~UserList() {
    for (auto user : users) {
        delete user;
    }
}