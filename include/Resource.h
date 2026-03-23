//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_RESOURCE_H
#define LIBRARY_SYS_RESOURCE_H

#include <string>

/**
 * @brief Defines the virtual Resource class including the private fields, constructors and virtual functions.
 */
class Resource {
protected: // Private fields
    bool canLend;
    int ID;
    bool isBorrowed;
    std::string title;

public:
    // Constructor
    Resource(bool canLend, // Passed by value, since bool is cheaper to copy in memory
        int ID, // Passed by value, since int is cheaper to copy in memory
        bool isBorrowed, // Passed by value, since bool is cheaper to copy in memory
        const std::string& title // Passed by reference, since it's cheaper to reference the memory location of string.
        ) : canLend(canLend), ID(ID), isBorrowed(isBorrowed), title(title) {}

    // Accessors
    virtual bool getLend() const;
    virtual int getID() const;
    virtual bool getBorrowed() const;
    virtual std::string getTitle() const;

    // Virtual Destructor
    virtual ~Resource() = default;
};

#endif //LIBRARY_SYS_RESOURCE_H