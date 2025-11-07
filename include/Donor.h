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
    void registerDonor(DatabaseManager& db); // existing console version

    //  UI-friendly registration (called from GUIManager)
    bool registerDonor(DatabaseManager& db,
                       const std::string& name_,
                       int age_,
                       const std::string& gender_,
                       const std::string& phone_,
                       const std::string& city_,
                       const std::string& address_,
                       const std::string& bloodGroup_,
                       bool healthTestStatus_);

    bool checkEligibility();
    void updateAvailability(DatabaseManager& db, bool newStatus);
    void updateEligibility(DatabaseManager& db);
    void showDonationHistory(DatabaseManager& db);
};
