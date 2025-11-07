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
};

