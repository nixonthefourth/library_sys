//
// Created by Mykyta Khomiakov on 23/03/2026.
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
 * All accessors are virtual so any future subclass can override them
 * without changing calling code in LibrarySystem.
 */
class Resource {
protected:
    bool canLend; /// Whether this resource type can be loaned out
    std::string ID; /// Unique string identifier (e.g. "B3", "J1", "C7")
    bool isBorrowed; /// True while the resource is on loan
    std::string title; /// Human-readable title of the resource

public:

    /**
     * @brief Constructs a Resource with all core fields.
     *
     * @param canLend Passed by value – bool is cheaper to copy than reference.
     * @param ID Passed by const-ref – avoids copying the string.
     * @param isBorrowed Passed by value – bool is cheaper to copy than reference.
     * @param title Passed by const-ref - avoids copying the string.
     */
    Resource(bool canLend,
             const std::string& ID,
             bool isBorrowed,
             const std::string& title)
        : canLend(canLend), ID(ID), isBorrowed(isBorrowed), title(title) {}

    /**
     * @return Whether this resource type permits lending.
     */
    virtual bool getLend() const;

    /**
     * @return The unique string ID of this resource.
     */
    virtual std::string getID() const;

    /**
     * @return True if the resource is currently on loan.
     */
    virtual bool getBorrowed() const;

    /**
     * @return The human-readable title of this resource.
     */
    virtual std::string getTitle() const;

    /**
     * @brief Sets the borrowed flag directly.
     *
     * Called by Loan::issueLoan() and Loan::returnLoan() – not intended
     * for use outside the loan management flow.
     *
     * @param status True to mark as borrowed; false to mark as available.
     */
    void setBorrowed(bool status);

    /// Virtual destructor – required for safe polymorphic deletion.
    virtual ~Resource() = default;
};

#endif //LIBRARY_SYS_RESOURCE_H