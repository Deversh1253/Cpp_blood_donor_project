#pragma once
#include "DatabaseManager.h"

class Donor {
private:
    string name, gender, phone, city, address, bloodGroup;
    int age;
    bool available, healthTestStatus, eligibilityStatus, approvalStatus;
    string lastDonationDate;

public:
    Donor();
    void registerDonor(DatabaseManager& db);
    bool checkEligibility();
    void updateAvailability(DatabaseManager& db, bool newStatus);
    void showDonationHistory(DatabaseManager& db);
};

