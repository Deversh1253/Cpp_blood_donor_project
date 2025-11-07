#include "SearchLog.h"
#include <iostream>
using namespace std;

// Save search details to DB
bool SearchLog::logSearch(DatabaseManager& db, int hospitalID, const string& bloodGroup, const string& area) {
    string query = "INSERT INTO SearchLog(hospitalID, bloodGroup, area, searchDate) VALUES(" +
                   to_string(hospitalID) + ", '" + bloodGroup + "', '" + area + "', CURRENT_DATE)";

    if (db.executeQuery(query)) {
        cout << "✅ Search successfully logged in database.\n";
        return true;
    } else {
        cout << "❌ Failed to log search.\n";
        return false;
    }
}

// Retrieve search history for a hospital
vector<vector<string>> SearchLog::getSearchHistory(DatabaseManager& db, int hospitalID) {
    string query = "SELECT logID, bloodGroup, area, searchDate FROM SearchLog WHERE hospitalID = " +
                   to_string(hospitalID) + " ORDER BY searchDate DESC";

    return db.fetchResults(query);
}

