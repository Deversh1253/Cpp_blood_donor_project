#pragma once
#include "DatabaseManager.h"

class Admin {
public:
    void approveDonor(DatabaseManager& db, std::string phone);
    void rejectDonor(DatabaseManager& db, std::string phone); // (console-based)
    void rejectDonor(DatabaseManager& db, std::string phone, const std::string& reason); // GUI  with reasoning option
    void removeInactiveDonor(DatabaseManager& db);
};
