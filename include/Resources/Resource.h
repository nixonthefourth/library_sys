//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_RESOURCE_H
#define LIBRARY_SYS_RESOURCE_H

#include <string>

/**
 * @brief Abstract base class for all library resources.
 *
 * Defines the common interface shared by Book, Journal, and Conference.
 * Concrete subclasses pass their type-specific lendability flag through
 * the constructor rather than overriding getLend(), keeping the hierarchy flat.
 *
 * The author field is populated for Books; it is left empty for Journals
 * and Conferences, which have no single author in the data file.
 *
 * All accessors are virtual so any future subclass can override them
 * without changing calling code in LibrarySystem.
 */
class Resource {
protected:
    bool canLend; /// Whether this resource type can be loaned out
    std::string ID; /// Unique string identifier (e.g. "B3", "J1", "C7")
    bool isBorrowed; /// True while the resource is on loan
    std::string title; /// Human-readable title of the resource
    std::string author; /// Author name – populated for Books; empty for others

public:

    /**
     * @brief Constructs a Resource with all core fields.
     *
     * @param canLend Passed by value – bool is cheaper to copy than reference.
     * @param ID Passed by const-ref – avoids copying the string.
     * @param isBorrowed Passed by value – bool is cheaper to copy than reference.
     * @param title Passed by const-ref – avoids copying the string.
     * @param author Passed by const-ref – avoids copying the string. Empty by default.
     */
    Resource(bool canLend,
             const std::string& ID,
             bool isBorrowed,
             const std::string& title,
             const std::string& author = "")
        : canLend(canLend), ID(ID), isBorrowed(isBorrowed),
          title(title), author(author) {}

    virtual bool getLend() const;
    virtual std::string getID() const;
    virtual bool getBorrowed() const;
    virtual std::string getTitle() const;

    /**
     * @return The author name, or an empty string for non-book resources.
     */
    virtual std::string getAuthor() const;

    /**
     * @brief Sets the borrowed flag.
     * Called by Loan::issueLoan() and Loan::returnLoan() only.
     * @param status True = borrowed; false = available.
     */
    void setBorrowed(bool status);

    virtual ~Resource() = default;
};

#endif //LIBRARY_SYS_RESOURCE_H