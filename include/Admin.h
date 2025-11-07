#pragma once
#include "DatabaseManager.h"

class Admin {
public:
    void approveDonor(DatabaseManager& db, string phone);
    void rejectDonor(DatabaseManager& db, string phone);
    void removeInactiveDonor(DatabaseManager& db);
};

