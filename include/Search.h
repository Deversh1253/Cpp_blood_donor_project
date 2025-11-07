#pragma once
#include "DatabaseManager.h"
#include <vector>
#include <string>

class Search {
private:
    std::string bloodGroup;
    std::string city;
    std::vector<std::vector<std::string>> results;
    int resultCount = 0;

public:
    // Executes donor search (fetches from DB, stores in memory)
    int executeSearch(DatabaseManager& db, const std::string& bloodGroup, const std::string& city);

    // Clears temporary results from memory
    void clearMemory();

    // Getters
    const std::vector<std::vector<std::string>>& getResults() const { return results; }
    int getResultCount() const { return resultCount; }
    const std::string& getBloodGroup() const { return bloodGroup; }
    const std::string& getCity() const { return city; }
};

