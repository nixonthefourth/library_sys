//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "Logic/UserList.h"
#include "Users/Student.h"
#include "Users/Staff.h"
#include "Users/LibStaff.h"

#include <fstream>
#include <iostream>

// ────────────────────────────────────────────────────────────────────────────
// File parsing
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Parses the user data file into Student, Staff, and LibStaff objects.
 *
 * File format
 *
 * Each non-empty line encodes one user.  The first character is the type
 * code; everything after it is the display name:
 *
 * | Code | Type     | Borrow limit |
 * |------|----------|--------------|
 * | '1'  | Student  | 1            |
 * | '2'  | Staff    | 2            |
 * | '3'  | LibStaff | 0            |
 *
 * Line-ending safety
 *
 * Trailing \r is stripped after each getline call so the loader handles
 * Windows CRLF files correctly on macOS/Linux.  Without this strip, names
 * would be stored with an embedded \r, which causes the terminal cursor to
 * return to column zero mid-line and silently overwrite report output.
 *
 * ID assignment
 *
 * IDs are assigned sequentially starting from 1 and increment only when
 * a valid user is successfully constructed and pushed into the vector.
 *
 * @param filename  Path to the user data file.
 */
void UserList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open user file: " << filename << "\n";
        return;
    }

    std::string line;
    int idCounter = 1;

    while (std::getline(file, line)) {

        // Strip Windows-style carriage return if present
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        // First character encodes the user type
        char type = line[0];

        // Everything after the type code is the display name
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

        // Unknown type codes are silently skipped – the ID counter does not advance
        if (user != nullptr) {
            users.push_back(user);
            idCounter++;
        }
    }

    std::cout << "  Loaded " << users.size() << " users.\n";
    file.close();
}

// ────────────────────────────────────────────────────────────────────────────
// Accessors
// ────────────────────────────────────────────────────────────────────────────

/**
 * @return A copy of the internal user pointer vector.
 *         Callers must not delete any of the returned pointers — ownership
 *         stays with this UserList.
 */
std::vector<Person*> UserList::getUsers() const {
    return users;
}

/**
 * @brief Linear scan for a user matching the given integer ID.
 *
 * @param id  The integer ID to match.
 * @return    Pointer to the matching Person, or nullptr if not found.
 */
Person* UserList::findByID(int id) const {
    for (auto user : users) {
        if (user->getID() == id) {
            return user;
        }
    }
    return nullptr;
}

// ────────────────────────────────────────────────────────────────────────────
// Destructor
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Deletes all heap-allocated Person objects.
 *
 * UserList is the sole owner of these pointers — nothing else should
 * delete them.
 */
UserList::~UserList() {
    for (auto user : users) {
        delete user;
    }
}