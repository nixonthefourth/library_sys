//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#include "Logic/ResourceList.h"
#include "Resources/Book.h"
#include "Resources/Journal.h"
#include "Resources/Conference.h"

#include <fstream>
#include <iostream>
#include <algorithm>

// ────────────────────────────────────────────────────────────────────────────
// Internal helpers
// ────────────────────────────────────────────────────────────────────────────

namespace {
    /**
     * @brief Returns a lowercase copy of s for case-insensitive comparisons.
     */
    std::string toLower(const std::string& s) {
        std::string out = s;
        std::transform(out.begin(), out.end(), out.begin(), ::tolower);
        return out;
    }

} // anonymous namespace

// ────────────────────────────────────────────────────────────────────────────
// File parsing
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Parses the resource data file into Book, Journal, and Conference objects.
 *
 * File format
 *
 * The file is divided into three data sections by "#####" separator lines.
 * A header block (two "#####" lines with comments between them) precedes
 * the data, so the section counter starts at -1 and reaches 1 on the
 * second separator.
 *
 * | Section | Content      | Lines per entry           |
 * |---------|--------------|---------------------------|
 * | 1       | Books        | author, title, year (x3)  |
 * | 2       | Journals     | title, vol1, vol2  (x3)   |
 * | 3       | Conferences  | title + N acronym lines   |
 *
 * Author storage
 *
 * The author line is now forwarded to the Book constructor so that
 * sort-by-author and keyword search work correctly.
 *
 * Line-ending safety
 *
 * All lines are read into a vector and stripped of trailing \r before
 * parsing begins, making the loader robust against Windows CRLF files
 * on UNIX.
 *
 * Why index-based iteration
 *
 * An explicit index (i) is used so multi-line entries can be consumed
 * by advancing i, and so the conference parser can peek at lines[i+1]
 * without any seekg calls.  seekg after getline on a buffered ifstream
 * is unreliable and was the source of an earlier parsing bug.
 *
 * @param filename  Path to the resource data file.
 */
void ResourceList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open resource file: " << filename << "\n";
        return;
    }

    // Read every line into a vector, stripping \r for cross-platform safety
    std::vector<std::string> lines;
    std::string raw;
    while (std::getline(file, raw)) {
        if (!raw.empty() && raw.back() == '\r')
            raw.pop_back();
        lines.push_back(raw);
    }

    int section = -1; // Increments each time a ##### separator is encountered
    int bookID = 1;  // Per-type counters give clean IDs: B1..B10, J1..J2, C1..C16
    int journalID = 1;
    int confID = 1;

    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];

        // ---- section separator ----
        if (line.find("#####") != std::string::npos) {
            section++;
            continue;
        }

        // ---- skip comments and blank lines ----
        if (line.empty() || line[0] == '#') continue;

        // ─────────────────────────────────────────
        // SECTION 1 – BOOKS
        // Three consecutive lines: author / title / year
        // ─────────────────────────────────────────
        if (section == 1) {
            if (i + 2 >= lines.size()) break; // malformed file guard

            const std::string& author = line; // lines[i]   = author
            const std::string& title  = lines[i + 1]; // lines[i+1] = title
            // lines[i+2] = year, not stored
            i += 2;

            std::string id = "B" + std::to_string(bookID++);
            resources.push_back(new Book(id, false, title, author));
        }

        // ─────────────────────────────────────────
        // SECTION 2 – JOURNALS
        // Three consecutive lines: title / volume line 1 / volume line 2
        // ─────────────────────────────────────────
        else if (section == 2) {

            if (i + 2 >= lines.size()) break; // malformed file guard

            const std::string& title = line;
            i += 2; // skip the two volume lines

            std::string id = "J" + std::to_string(journalID++);
            resources.push_back(new Journal(id, false, title));
        }

        // ─────────────────────────────────────────
        // SECTION 3 – CONFERENCES
        // Variable-length: title line (contains spaces) + N acronym lines (no spaces)
        // ─────────────────────────────────────────
        else if (section == 3) {
            const std::string& title = line;

            while (i + 1 < lines.size()) {
                const std::string& next = lines[i + 1];

                // End of section
                if (next.find("#####") != std::string::npos) {
                    section++;
                    i++;
                    break;
                }

                // Blank or comment – skip without breaking
                if (next.empty() || next[0] == '#') {
                    i++;
                    continue;
                }

                // A line with a space is the start of the next conference title
                if (next.find(' ') != std::string::npos) {
                    break;
                }

                // No space: acronym for the current conference
                i++;
                std::string id = "C" + std::to_string(confID++);
                resources.push_back(new Conference(id, false, title, next));
            }
        }
    }

    std::cout << "  Loaded " << resources.size() << " resources.\n";
}

// ────────────────────────────────────────────────────────────────────────────
// Accessors
// ────────────────────────────────────────────────────────────────────────────

/**
 * @return A copy of the internal resource pointer vector.
 *         Callers must not delete any of the returned pointers.
 */
std::vector<Resource*> ResourceList::getResources() const {
    return resources;
}

/**
 * @brief Linear scan for a resource matching the given ID string.
 *
 * @param id The ID to match (case-sensitive).
 * @return Pointer to the matching Resource, or nullptr if not found.
 */
Resource* ResourceList::findByID(const std::string& id) const {
    for (auto r : resources) {
        if (r->getID() == id) {
            return r;
        }
    }
    return nullptr;
}

// ────────────────────────────────────────────────────────────────────────────
// Search
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Case-insensitive keyword search across title, author, and acronym.
 *
 * The keyword is lowercased once, then each resource's title and author
 * are lowercased for comparison.  For Conference resources a dynamic_cast
 * retrieves the acronym without modifying the class hierarchy.
 *
 * Results are sorted alphabetically by title before returning.
 *
 * @param keyword The search term.
 * @return Sorted vector of matching Resource pointers.
 */
std::vector<Resource*> ResourceList::searchByKeyword(const std::string& keyword) const {
    const std::string key = toLower(keyword);
    std::vector<Resource*> results;

    for (auto r : resources) {

        bool matchTitle  = toLower(r->getTitle()).find(key)  != std::string::npos;
        bool matchAuthor = toLower(r->getAuthor()).find(key) != std::string::npos;

        // Check acronym for Conference resources via dynamic_cast
        bool matchAcronym = false;
        if (auto* conf = dynamic_cast<Conference*>(r)) {
            matchAcronym = toLower(conf->getTitleAcronym()).find(key) != std::string::npos;
        }

        if (matchTitle || matchAuthor || matchAcronym) {
            results.push_back(r);
        }
    }

    // Sort alphabetically by title
    std::sort(results.begin(), results.end(),
        [](Resource* a, Resource* b) {
            return a->getTitle() < b->getTitle();
        });

    return results;
}

// ────────────────────────────────────────────────────────────────────────────
// Destructor
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Deletes all heap-allocated Resource objects.
 *
 * ResourceList is the sole owner of these pointers.
 */
ResourceList::~ResourceList() {
    for (auto r : resources) {
        delete r;
    }
}