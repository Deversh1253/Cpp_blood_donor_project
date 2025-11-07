#include "Search.h"
#include "SearchLog.h"

int main() {
    DatabaseManager db;
    if (!db.connectDB()) return 0;

    Donor donor;
    Admin admin;
    Hospital hospital;
    Search search; // temporary search memory
    int hospitalID = 1; // for demo/testing

    int choice;
    do {
        cout << "\n===== BLOOD LIFE MENU =====\n";
        cout << "1. Register as Donor\n";
        cout << "2. Admin - Approve Donor\n";
        cout << "3. Hospital - Search Donors\n";
        cout << "4. Save Search to Database\n";
        cout << "5. View Search History\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            donor.registerDonor(db);
            break;

        case 2: {
            string phone;
            cout << "Enter donor phone to approve: ";
            getline(cin, phone);
            admin.approveDonor(db, phone);
            break;
        }

        case 3: {
            string bg, cty;
            cout << "Enter blood group: ";
            getline(cin, bg);
            cout << "Enter city: ";
            getline(cin, cty);
            search.executeSearch(db, bg, cty);
            break;
        }

        case 4: {
            if (search.getResultCount() == 0) {
                cout << "⚠️ No search in memory to save.\n";
            } else {
                string area;
                cout << "Enter area to save in log: ";
                getline(cin, area);
                if (SearchLog::logSearch(db, hospitalID, search.getBloodGroup(), area)) {
                    search.clearMemory(); // clear in-memory data after saving
                }
            }
            break;
        }

        case 5: {
            cout << "\n--- Search History ---\n";
            auto history = SearchLog::getSearchHistory(db, hospitalID);
            if (history.empty()) cout << "No past searches found.\n";
            for (auto& row : history) {
                for (auto& col : row) cout << col << "\t";
                cout << endl;
            }
            break;
        }

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    db.closeConnection();
    return 0;
}

