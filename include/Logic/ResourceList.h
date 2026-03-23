//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#ifndef LIBRARY_SYS_RESOURCELIST_H
#define LIBRARY_SYS_RESOURCELIST_H

#include <vector>
#include <string>
#include "Resources/Resource.h"

class ResourceList {
private:
    std::vector<Resource*> resources;

public:
    void loadFromFile(const std::string& filename);

    std::vector<Resource*> getResources() const;

    Resource* findByID(const std::string& id) const;

    ~ResourceList(); // cleanup
};

#endif