//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Logic/ResourceList.h"
#include "Resources/Book.h"
#include "Resources/Journal.h"
#include "Resources/Conference.h"

#include <fstream>
#include <iostream>
#include <sstream>

void ResourceList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }

    // Read every line into a vector first, stripping \r so Windows line-endings
    // don't silently corrupt string comparisons or ID generation.
    std::vector<std::string> lines;
    std::string raw;
    while (std::getline(file, raw)) {
        if (!raw.empty() && raw.back() == '\r')
            raw.pop_back();
        lines.push_back(raw);
    }

    int section    = -1;
    int bookID     = 1;
    int journalID  = 1;
    int confID     = 1;

    // We walk through the lines with an explicit index so we can advance
    // by multiple lines at once without any seekg trickery.
    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];

        // ---------- section separator ----------
        if (line.find("#####") != std::string::npos) {
            section++;
            continue;
        }

        // ---------- skip comments and blank lines ----------
        if (line.empty() || line[0] == '#') continue;

        // ============================================================
        // SECTION 1 — BOOKS
        // Format (3 lines per book):
        //   Author Surname, First name
        //   Title
        //   Year
        // ============================================================
        if (section == 1) {
            // line   = author  (already in `line`)
            // line+1 = title
            // line+2 = year
            if (i + 2 >= lines.size()) break; // malformed file guard

            const std::string& title = lines[i + 1];
            // lines[i + 2] is the year — we store it for future use if needed
            i += 2; // consume title and year lines

            std::string id = "B" + std::to_string(bookID++);
            resources.push_back(new Book(id, false, title));
        }

        // ============================================================
        // SECTION 2 — JOURNALS
        // Format (3 lines per journal):
        //   Journal title
        //   Volume line 1  (e.g. "1:1 2 3 4")
        //   Volume line 2  (e.g. "2:1 2 3 4")
        // ============================================================
        else if (section == 2) {
            const std::string& title = line;

            if (i + 2 >= lines.size()) break; // malformed file guard
            i += 2; // skip the two volume lines

            std::string id = "J" + std::to_string(journalID++);
            resources.push_back(new Journal(id, false, title));
        }

        // ============================================================
        // SECTION 3 — CONFERENCES
        // Format (variable lines per conference):
        //   Conference full title          <- contains spaces
        //   ACRONYM2025                    <- no spaces
        //   ACRONYM2024                    <- no spaces
        //   ...
        // A new conference begins whenever we encounter a line with spaces.
        // We detect it with a simple helper: if a line contains a space it is
        // a title; if it has no spaces it is an acronym.
        // ============================================================
        else if (section == 3) {
            // `line` is the conference title (it contains spaces)
            const std::string& title = line;

            // Gather all following acronym lines that belong to this title.
            // Stop when we hit: another title (has a space), a section marker,
            // a comment, or EOF.
            while (i + 1 < lines.size()) {
                const std::string& next = lines[i + 1];

                // End of section
                if (next.find("#####") != std::string::npos) {
                    section++;
                    i++; // consume the ##### line so the outer loop doesn't re-process it
                    break;
                }

                // Blank or comment — skip silently
                if (next.empty() || next[0] == '#') {
                    i++;
                    continue;
                }

                // If the next line contains a space it is the start of a new
                // conference title — leave it for the outer loop to handle.
                if (next.find(' ') != std::string::npos) {
                    break;
                }

                // Otherwise it is an acronym for the current conference.
                i++;
                std::string id = "C" + std::to_string(confID++);
                resources.push_back(new Conference(id, false, title, next));
            }
        }
    }

    std::cout << "Loaded resources: " << resources.size() << "\n";
}

// Utility Functions
std::vector<Resource*> ResourceList::getResources() const {
    return resources;
}

Resource* ResourceList::findByID(const std::string& id) const {
    for (auto r : resources) {
        if (r->getID() == id) {
            return r;
        }
    }
    return nullptr;
}

// Destructor
ResourceList::~ResourceList() {
    for (auto r : resources) {
        delete r;
    }
}