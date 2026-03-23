//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Logic/ResourceList.h"
#include "Resources/Book.h"
#include "Resources/Journal.h"
#include "Resources/Conference.h"

#include <fstream>
#include <iostream>

// ────────────────────────────────────────────────────────────────────────────
// File parsing
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Parses the resource data file into Book, Journal, and Conference objects.
 *
 * ### File format
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
 * ### Line-ending safety
 * All lines are read into a vector and stripped of trailing \r before
 * parsing begins.  This makes the loader robust against Windows CRLF
 * files being opened on macOS or Linux, where getline would otherwise
 * leave a \r at the end of every string.
 *
 * ### Why index-based iteration
 * An explicit index (i) is used instead of getline on the stream so
 * that multi-line entries can be consumed by advancing i, and so the
 * conference parser can peek ahead at lines[i+1] without any seekg
 * calls.  seekg after getline on a buffered ifstream is unreliable
 * and was the source of an earlier parsing bug.
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

    int section   = -1; // Increments each time a ##### line is encountered
    int bookID    = 1;  // Per-type counters give clean IDs: B1..B10, J1..J2, C1..C16
    int journalID = 1;
    int confID    = 1;

    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];

        // ---- section separator ----
        if (line.find("#####") != std::string::npos) {
            section++;
            continue;
        }

        // ---- skip comments and blank lines ----
        if (line.empty() || line[0] == '#') continue;

        // ════════════════════════════════════════
        // SECTION 1 — BOOKS
        // Three consecutive lines: author / title / year
        // We only store title; author and year are consumed but not saved.
        // ════════════════════════════════════════
        if (section == 1) {

            if (i + 2 >= lines.size()) break; // malformed file guard

            // lines[i]   = author  (already in `line`, not stored)
            // lines[i+1] = title
            // lines[i+2] = year   (consumed, not stored)
            const std::string& title = lines[i + 1];
            i += 2; // consume title and year so the outer loop skips them

            std::string id = "B" + std::to_string(bookID++);
            resources.push_back(new Book(id, false, title));
        }

        // ════════════════════════════════════════
        // SECTION 2 — JOURNALS
        // Three consecutive lines: title / volume line 1 / volume line 2
        // Volume data is consumed but not stored at this stage.
        // ════════════════════════════════════════
        else if (section == 2) {

            if (i + 2 >= lines.size()) break; // malformed file guard

            const std::string& title = line;
            i += 2; // skip the two volume lines

            std::string id = "J" + std::to_string(journalID++);
            resources.push_back(new Journal(id, false, title));
        }

        // ════════════════════════════════════════
        // SECTION 3 — CONFERENCES
        // Variable-length entries: one title line (contains spaces) followed
        // by one or more acronym lines (no spaces, e.g. "CHI2025").
        // A new conference begins whenever a line containing a space is found.
        // ════════════════════════════════════════
        else if (section == 3) {

            // `line` is the conference title — it always contains spaces
            const std::string& title = line;

            // Consume all acronym lines that follow this title
            while (i + 1 < lines.size()) {
                const std::string& next = lines[i + 1];

                // End of section — advance past the separator and stop
                if (next.find("#####") != std::string::npos) {
                    section++;
                    i++;
                    break;
                }

                // Blank or comment — skip silently without breaking the loop
                if (next.empty() || next[0] == '#') {
                    i++;
                    continue;
                }

                // A line containing a space is a new conference title —
                // leave i where it is so the outer loop picks it up next
                if (next.find(' ') != std::string::npos) {
                    break;
                }

                // No space → this is an acronym for the current conference
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
 *         Callers must not delete any of the returned pointers — ownership
 *         stays with this ResourceList.
 */
std::vector<Resource*> ResourceList::getResources() const {
    return resources;
}

/**
 * @brief Linear scan for a resource matching the given ID string.
 *
 * Performance is acceptable for the small data sets this system targets.
 *
 * @param id  The ID to match (case-sensitive, e.g. "B3", "J1", "C7").
 * @return    Pointer to the matching Resource, or nullptr if not found.
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
// Destructor
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Deletes all heap-allocated Resource objects.
 *
 * ResourceList is the sole owner of these pointers — nothing else should
 * delete them.
 */
ResourceList::~ResourceList() {
    for (auto r : resources) {
        delete r;
    }
}