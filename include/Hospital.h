#pragma once
#include "DatabaseManager.h"

class Hospital {
public:
    void findDonors(DatabaseManager& db, string bloodGroup, string city);
};

