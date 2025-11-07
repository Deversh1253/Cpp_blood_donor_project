#pragma once
#include "DatabaseManager.h"
#include <string>
#include <vector>

class SearchLog {
public:
    // Save the last search permanently
    static bool logSearch(DatabaseManager& db, int hospitalID, const std::string& bloodGroup, const std::string& area);

    // Retrieve all past searches for a hospital
    static std::vector<std::vector<std::string>> getSearchHistory(DatabaseManager& db, int hospitalID);
};

