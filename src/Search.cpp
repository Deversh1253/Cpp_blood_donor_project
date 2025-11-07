#include "Search.h"
#include <iostream>
using namespace std;

// Executes donor search and holds data temporarily
int Search::executeSearch(DatabaseManager& db, const string& bg, const string& cty) {
    bloodGroup = bg;
    city = cty;
    results.clear();

    string query = "SELECT name, phone, city, bloodGroup FROM Donor "
                   "WHERE bloodGroup = '" + bg + "' "
                   "AND city = '" + cty + "' "
                   "AND approvalStatus = 1 AND available = 1";

    results = db.fetchResults(query);
    resultCount = static_cast<int>(results.size());

    cout << "\n🔍 Search completed! " << resultCount << " donor(s) found.\n";
    for (auto& row : results) {
        for (auto& col : row)
            cout << col << "\t";
        cout << endl;
    }

    return resultCount;
}

// Clears all temporary memory data
void Search::clearMemory() {
    results.clear();
    resultCount = 0;
    bloodGroup.clear();
    city.clear();
    cout << "🧹 Temporary search data cleared from memory.\n";
}
