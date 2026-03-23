//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Logic/ResourceList.h"
#include "Resources/Book.h"
#include "Resources/Journal.h"
#include "Resources/Conference.h"

#include <fstream>
#include <iostream>

void ResourceList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    // Opening check
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }

    std::string line;
    int section = 0;
    int idCounter = 1;

    while (std::getline(file, line)) {

        // Section switch
        if (line == "#####") {
            section++;
            continue;
        }

        if (line.empty()) continue;

        // Books
        if (section == 1) {
            std::string author = line;

            std::string title;
            std::getline(file, title);

            std::string year;
            std::getline(file, year);

            std::string id = "B" + std::to_string(idCounter++);

            resources.push_back(new Book(id, false, title));
        }

        // Journals
        else if (section == 2) {
            std::string title = line;

            std::string issues;
            std::getline(file, issues);

            std::string id = "J" + std::to_string(idCounter++);

            resources.push_back(new Journal(id, false, title));
        }

        // Conferences
        else if (section == 3) {
            std::string title = line;

            std::string acronym;
            while (std::getline(file, acronym)) {
                if (acronym.empty() || acronym == "#####") break;

                std::string id = "C" + std::to_string(idCounter++);

                resources.push_back(new Conference(id, false, title, acronym));
            }
        }
    }

    file.close();
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