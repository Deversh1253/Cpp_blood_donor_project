#pragma once
#include "DatabaseManager.h"
#include <vector>
#include <string>

class Analytics {
public:
    // Count of searches by blood group (optionally by area)
    static std::vector<std::vector<std::string>>
    showDemandByBloodGroup(DatabaseManager& db);

    static std::vector<std::vector<std::string>>
    showAreaWiseTrends(DatabaseManager& db);

    // --- GUI helpers: header names for table display
    static std::vector<std::string> demandByBloodGroupHeaders();
    static std::vector<std::string> areaWiseTrendsHeaders();

    // --- Future enhancements: export / chart helpers
    // Export given results to a CSV file (returns true on success)
    static bool exportResultsToCSV(const std::string& filename,
                                   const std::vector<std::string>& headers,
                                   const std::vector<std::vector<std::string>>& rows);

    // (Optional) Generate a simple CSV that can be plotted externally.
    static bool generateDemandCSV(DatabaseManager& db, const std::string& outFile);
};
