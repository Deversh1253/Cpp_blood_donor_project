#include "Analytics.h"
#include <fstream>

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

// GUI header strings
std::vector<std::string> Analytics::demandByBloodGroupHeaders() {
    return { "Blood Group", "Total Searches" };
}

std::vector<std::string> Analytics::areaWiseTrendsHeaders() {
    return { "Area", "Blood Group", "Count" };
}

// Export rows (headers + rows) to CSV
bool Analytics::exportResultsToCSV(const std::string& filename,
                                   const std::vector<std::string>& headers,
                                   const std::vector<std::vector<std::string>>& rows) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    // write headers
    for (size_t i = 0; i < headers.size(); ++i) {
        out << headers[i];
        if (i + 1 < headers.size()) out << ",";
    }
    out << "\n";

    // write rows
    for (const auto& r : rows) {
        for (size_t j = 0; j < r.size(); ++j) {
            // naive CSV escaping: wrap in quotes if contains comma
            std::string cell = r[j];
            bool needQuotes = (cell.find(',') != std::string::npos);
            if (needQuotes) out << '"';
            out << cell;
            if (needQuotes) out << '"';
            if (j + 1 < r.size()) out << ",";
        }
        out << "\n";
    }

    out.close();
    return true;
}

// Convenience function to export demand-by-blood-group to CSV directly
bool Analytics::generateDemandCSV(DatabaseManager& db, const std::string& outFile) {
    auto rows = showDemandByBloodGroup(db);
    auto headers = demandByBloodGroupHeaders();
    return exportResultsToCSV(outFile, headers, rows);
}
