#include "Donor.h"
#include <iostream>
using namespace std;

Donor::Donor() {
    available = healthTestStatus = eligibilityStatus = approvalStatus = false;
}

bool Donor::checkEligibility() {
    return (age >= 18 && age <= 65 && healthTestStatus);
}

void Donor::registerDonor(DatabaseManager& db) {
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Age: "; cin >> age; cin.ignore();
    cout << "Enter Gender: "; getline(cin, gender);
    cout << "Enter Phone: "; getline(cin, phone);
    cout << "Enter City: "; getline(cin, city);
    cout << "Enter Address: "; getline(cin, address);
    cout << "Enter Blood Group: "; getline(cin, bloodGroup);
    cout << "Have you passed health test (1/0): "; cin >> healthTestStatus;

    eligibilityStatus = checkEligibility();
    approvalStatus = false;

    string query = "INSERT INTO Donor(name, age, gender, phone, city, address, bloodGroup, available, healthTestStatus, eligibilityStatus, approvalStatus) VALUES('" +
                   name + "', " + to_string(age) + ", '" + gender + "', '" + phone + "', '" + city + "', '" +
                   address + "', '" + bloodGroup + "', 0, " + to_string(healthTestStatus) + ", " +
                   to_string(eligibilityStatus) + ", 0)";

    if (db.executeQuery(query))
        cout << "✅ Donor registration request submitted!\n";
}

void Donor::updateAvailability(DatabaseManager& db, bool newStatus) {
    available = newStatus;
    string query = "UPDATE Donor SET available = " + to_string(available) + " WHERE phone = '" + phone + "'";
    db.executeQuery(query);
    cout << "Availability updated successfully.\n";
}

void Donor::showDonationHistory(DatabaseManager& db) {
    auto result = db.fetchResults("SELECT name, bloodGroup, city, lastDonationDate FROM Donor WHERE phone = '" + phone + "'");
    for (auto& row : result) {
        for (auto& col : row)
            cout << col << " ";
        cout << endl;
    }
}

