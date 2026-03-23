//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_USERLIST_H
#define LIBRARY_SYS_USERLIST_H

#include <vector>
#include <string>
#include "Users/Person.h"

/**
 * @brief Container that owns all Person objects in the system.
 *
 * Parses A2UserList.txt into the three concrete user types
 * (Student, Staff, LibStaff) and provides lookup by integer ID.
 *
 * Owns the heap-allocated Person objects — the destructor deletes them.
 * Nothing else in the system should delete a Person* obtained from here.
 */
class UserList {
private:
    std::vector<Person*> users; ///< Heap-allocated user objects, owned by this list

public:

    /**
     * @brief Parses a user data file and populates the internal vector.
     *
     * Each non-empty line encodes one user: the first character is the type
     * code ('1' = Student, '2' = Staff, '3' = LibStaff) and the remainder
     * is the display name.  Trailing \r is stripped so the loader is robust
     * against Windows CRLF line endings on macOS/Linux.
     *
     * @param filename  Path to the user data file (relative to the working directory).
     */
    void loadFromFile(const std::string& filename);

    /**
     * @return A copy of the internal user pointer vector.
     *         Callers must not delete any of the returned pointers.
     */
    std::vector<Person*> getUsers() const;

    /**
     * @brief Looks up a user by their integer ID.
     *
     * @param id  The ID to search for.
     * @return    Pointer to the matching Person, or nullptr if not found.
     */
    Person* findByID(int id) const;

    /// Destructor — deletes all heap-allocated Person objects.
    ~UserList();
};

#endif //LIBRARY_SYS_USERLIST_H