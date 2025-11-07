#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <QTextEdit>

#include "DatabaseManager.h"
#include "Donor.h"
#include "Admin.h"
#include "Hospital.h"
#include "Search.h"
#include "Analytics.h"
#include "SearchLog.h"

class GUIManager : public QMainWindow {
    Q_OBJECT

public:
    GUIManager(QWidget* parent = nullptr);
    ~GUIManager();

private slots:
    // donor
    void onRegisterDonorClicked();

    // admin
    void onApproveDonorClicked();
    void onRejectDonorClicked();

    // hospital
    void onHospitalSearchClicked();
    void onSaveSearchClicked();

    // analytics
    void onShowDemandClicked();
    void onShowAreaTrendsClicked();
    void onExportDemandCSV();

private:
    // core DB manager
    DatabaseManager db;

    // UI elements
    QTabWidget* tabWidget;

    // Donor tab widgets
    QWidget* donorTab;
    QLineEdit* leName;
    QLineEdit* leAge;
    QComboBox* cbGender;
    QLineEdit* lePhone;
    QLineEdit* leCity;
    QLineEdit* leAddress;
    QComboBox* cbBloodGroup;
    QComboBox* cbHealthTest;
    QPushButton* btnRegisterDonor;
    QLabel* donorStatusLabel;

    // Admin tab
    QWidget* adminTab;
    QLineEdit* leAdminPhone;
    QPushButton* btnApproveDonor;
    QPushButton* btnRejectDonor;
    QLineEdit* leRejectReason;
    QLabel* adminStatusLabel;

    // Hospital tab
    QWidget* hospitalTab;
    QLineEdit* leSearchBlood;
    QLineEdit* leSearchCity;
    QPushButton* btnHospitalSearch;
    QTableWidget* tableResults;
    QPushButton* btnSaveSearch;
    QLineEdit* leHospitalArea; // for saving area to search log

    // Analytics tab
    QWidget* analyticsTab;
    QPushButton* btnShowDemand;
    QPushButton* btnShowAreaTrends;
    QPushButton* btnExportCSV;
    QLabel* analyticsStatusLabel;

    // helper
    void setupUI();
    void populateTable(const std::vector<std::vector<std::string>>& rows,
                       const std::vector<std::string>& headers = {});
};
