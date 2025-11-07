#include "Admin.h"
#include <iostream>
using namespace std;

void Admin::approveDonor(DatabaseManager& db, string phone) {
    string query = "UPDATE Donor SET approvalStatus = 1 WHERE phone = '" + phone + "'";
    if (db.executeQuery(query))
        cout << "✅ Donor approved successfully!\n";
}

void Admin::rejectDonor(DatabaseManager& db, string phone) {
    string reason;
    cout << "Enter rejection reason: ";
    getline(cin, reason);
    string query = "UPDATE Donor SET approvalStatus = 0, rejectionReason = '" + reason + "' WHERE phone = '" + phone + "'";
    db.executeQuery(query);
}

void Admin::removeInactiveDonor(DatabaseManager& db) {
    string query = "DELETE FROM Donor WHERE available = 0 AND approvalStatus = 1";
    if (db.executeQuery(query))
        cout << "🧹 Inactive donors removed successfully.\n";
}

