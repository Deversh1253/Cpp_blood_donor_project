#include "Hospital.h"
#include <iostream>
using namespace std;

void Hospital::findDonors(DatabaseManager& db, string bloodGroup, string city) {
    string query = "SELECT name, phone, city, bloodGroup FROM Donor WHERE bloodGroup = '" + bloodGroup +
                   "' AND city = '" + city + "' AND approvalStatus = 1 AND available = 1";

    auto results = db.fetchResults(query);
    cout << "\n--- Available Donors ---\n";
    for (auto& row : results) {
        for (auto& col : row)
            cout << col << "  ";
        cout << endl;
    }
    if (results.empty())
        cout << "No donors found.\n";
}
