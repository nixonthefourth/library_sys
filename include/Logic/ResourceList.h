//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_RESOURCELIST_H
#define LIBRARY_SYS_RESOURCELIST_H

#include <vector>
#include <string>
#include "Resources/Resource.h"

/**
 * @brief Container that owns all Resource objects in the system.
 *
 * Parses A2ResourceList.txt into the three concrete resource types
 * (Book, Journal, Conference) and provides lookup and search by various fields.
 *
 * Owns the heap-allocated Resource objects – the destructor deletes them.
 * Nothing else in the system should delete a Resource* obtained from here.
 */
class ResourceList {
private:
    std::vector<Resource*> resources; /// Heap-allocated resource objects, owned by this list

public:

    /**
     * @brief Parses a resource data file and populates the internal vector.
     *
     * All lines are stripped of trailing \r before parsing begins, making
     * the loader robust against Windows CRLF line endings on macOS/Linux.
     * Uses index-based iteration rather than seekg for reliable multi-line parsing.
     *
     * @param filename  Path to the resource data file.
     */
    void loadFromFile(const std::string& filename);

    /**
     * @return A copy of the internal resource pointer vector.
     *         Callers must not delete any of the returned pointers.
     */
    std::vector<Resource*> getResources() const;

    /**
     * @brief Looks up a resource by its string ID.
     *
     * @param id  The ID to search for (e.g. "B3", "J1", "C7").
     * @return    Pointer to the matching Resource, or nullptr if not found.
     */
    Resource* findByID(const std::string& id) const;

    /**
     * @brief Case-insensitive keyword search across title, author, and acronym fields.
     *
     * For each resource, the keyword is tested against:
     *   - title  (all types)
     *   - author (Books only – empty string for others, so the check is harmless)
     *   - acronym via dynamic_cast to Conference (acronyms have no spaces, e.g. "CHI2025")
     *
     * Results are returned sorted alphabetically by title.
     *
     * @param keyword The search term (case-insensitive).
     * @return Sorted vector of matching Resource pointers.
     */
    std::vector<Resource*> searchByKeyword(const std::string& keyword) const;

    /// Destructor – deletes all heap-allocated Resource objects.
    ~ResourceList();
};

#endif //LIBRARY_SYS_RESOURCELIST_H