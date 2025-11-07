#include "Analytics.h"

std::vector<std::vector<std::string>>
Analytics::showDemandByBloodGroup(DatabaseManager& db) {
    std::string q =
        "SELECT bloodGroup, COUNT(*) AS total_searches "
        "FROM SearchLog GROUP BY bloodGroup ORDER BY total_searches DESC";
    return db.fetchResults(q);
}

std::vector<std::vector<std::string>>
Analytics::showAreaWiseTrends(DatabaseManager& db) {
    std::string q =
        "SELECT area, bloodGroup, COUNT(*) AS cnt "
        "FROM SearchLog GROUP BY area, bloodGroup ORDER BY area ASC, cnt DESC";
    return db.fetchResults(q);
}

