#include "GUIManager.h"
#include <iostream>
using namespace std;

int GUIManager::displayMainMenu() {
    int choice;
    cout << "\n===== BLOOD LIFE MENU =====\n";
    cout << "1. Register as Donor\n";
    cout << "2. Admin - Approve Donor\n";
    cout << "3. Hospital - Search Donors (in-memory)\n";
    cout << "4. Hospital - Save Last Search to Log\n";
    cout << "5. Hospital - View Search History\n";
    cout << "6. Analytics - Demand by Blood Group\n";
    cout << "7. Analytics - Area-wise Trends\n";
    cout << "8. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

void GUIManager::showRows(const vector<vector<string>>& rows,
                          const vector<string>& headers) {
    if (!headers.empty()) {
        for (auto& h : headers) cout << h << "\t";
        cout << "\n";
    }
    if (rows.empty()) { cout << "(no rows)\n"; return; }
    for (auto& r : rows) {
        for (auto& c : r) cout << c << "\t";
        cout << "\n";
    }
}

