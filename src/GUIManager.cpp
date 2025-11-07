#include "GUIManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <sstream>

GUIManager::GUIManager(QWidget* parent) : QMainWindow(parent) {
    // Connect DB on startup
    if (!db.connectDB()) {
        QMessageBox::critical(this, "DB Error", "Failed to connect to MySQL database. Check credentials.");
        // still continue, but many features will fail
    }

    setupUI();
}

GUIManager::~GUIManager() {
    if (db.isConnected()) db.closeConnection();
}

void GUIManager::setupUI() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // ----------------- Donor Tab -----------------
    donorTab = new QWidget();
    QVBoxLayout* donorLayout = new QVBoxLayout();

    leName = new QLineEdit(); leName->setPlaceholderText("Full name");
    leAge = new QLineEdit(); leAge->setPlaceholderText("Age");
    cbGender = new QComboBox(); cbGender->addItems({ "Male", "Female", "Other" });
    lePhone = new QLineEdit(); lePhone->setPlaceholderText("Phone");
    leCity = new QLineEdit(); leCity->setPlaceholderText("City");
    leAddress = new QLineEdit(); leAddress->setPlaceholderText("Address");
    cbBloodGroup = new QComboBox(); cbBloodGroup->addItems({ "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-" });
    cbHealthTest = new QComboBox(); cbHealthTest->addItems({ "0", "1" }); // 0 = fail, 1 = pass
    btnRegisterDonor = new QPushButton("Register Donor");
    donorStatusLabel = new QLabel();

    donorLayout->addWidget(new QLabel("Name:")); donorLayout->addWidget(leName);
    donorLayout->addWidget(new QLabel("Age:")); donorLayout->addWidget(leAge);
    donorLayout->addWidget(new QLabel("Gender:")); donorLayout->addWidget(cbGender);
    donorLayout->addWidget(new QLabel("Phone:")); donorLayout->addWidget(lePhone);
    donorLayout->addWidget(new QLabel("City:")); donorLayout->addWidget(leCity);
    donorLayout->addWidget(new QLabel("Address:")); donorLayout->addWidget(leAddress);
    donorLayout->addWidget(new QLabel("Blood Group:")); donorLayout->addWidget(cbBloodGroup);
    donorLayout->addWidget(new QLabel("Health Test Passed (1 / 0):")); donorLayout->addWidget(cbHealthTest);
    donorLayout->addWidget(btnRegisterDonor);
    donorLayout->addWidget(donorStatusLabel);

    donorTab->setLayout(donorLayout);
    tabWidget->addTab(donorTab, "Donor");

    connect(btnRegisterDonor, &QPushButton::clicked, this, &GUIManager::onRegisterDonorClicked);

    // ----------------- Admin Tab -----------------
    adminTab = new QWidget();
    QVBoxLayout* adminLayout = new QVBoxLayout();

    leAdminPhone = new QLineEdit(); leAdminPhone->setPlaceholderText("Donor phone to approve/reject");
    btnApproveDonor = new QPushButton("Approve Donor");
    btnRejectDonor = new QPushButton("Reject Donor (with reason)");
    leRejectReason = new QLineEdit(); leRejectReason->setPlaceholderText("Rejection reason");
    adminStatusLabel = new QLabel();

    adminLayout->addWidget(new QLabel("Donor Phone:")); adminLayout->addWidget(leAdminPhone);
    adminLayout->addWidget(btnApproveDonor);
    adminLayout->addWidget(leRejectReason);
    adminLayout->addWidget(btnRejectDonor);
    adminLayout->addWidget(adminStatusLabel);

    adminTab->setLayout(adminLayout);
    tabWidget->addTab(adminTab, "Admin");

    connect(btnApproveDonor, &QPushButton::clicked, this, &GUIManager::onApproveDonorClicked);
    connect(btnRejectDonor, &QPushButton::clicked, this, &GUIManager::onRejectDonorClicked);

    // ----------------- Hospital Tab -----------------
    hospitalTab = new QWidget();
    QVBoxLayout* hospLayout = new QVBoxLayout();

    leSearchBlood = new QLineEdit(); leSearchBlood->setPlaceholderText("Blood Group");
    leSearchCity = new QLineEdit(); leSearchCity->setPlaceholderText("City");
    btnHospitalSearch = new QPushButton("Search Donors");
    tableResults = new QTableWidget();
    tableResults->setColumnCount(4);
    tableResults->setHorizontalHeaderLabels(QStringList() << "Name" << "Phone" << "City" << "Blood Group");
    tableResults->horizontalHeader()->setStretchLastSection(true);

    btnSaveSearch = new QPushButton("Save Last Search to Log");
    leHospitalArea = new QLineEdit(); leHospitalArea->setPlaceholderText("Area (for log)");

    hospLayout->addWidget(new QLabel("Blood Group:")); hospLayout->addWidget(leSearchBlood);
    hospLayout->addWidget(new QLabel("City:")); hospLayout->addWidget(leSearchCity);
    hospLayout->addWidget(btnHospitalSearch);
    hospLayout->addWidget(tableResults);
    hospLayout->addWidget(new QLabel("Area (for search log):")); hospLayout->addWidget(leHospitalArea);
    hospLayout->addWidget(btnSaveSearch);

    hospitalTab->setLayout(hospLayout);
    tabWidget->addTab(hospitalTab, "Hospital");

    connect(btnHospitalSearch, &QPushButton::clicked, this, &GUIManager::onHospitalSearchClicked);
    connect(btnSaveSearch, &QPushButton::clicked, this, &GUIManager::onSaveSearchClicked);

    // ----------------- Analytics Tab -----------------
    analyticsTab = new QWidget();
    QVBoxLayout* analyticsLayout = new QVBoxLayout();
    btnShowDemand = new QPushButton("Show Demand by Blood Group");
    btnShowAreaTrends = new QPushButton("Show Area-wise Trends");
    btnExportCSV = new QPushButton("Export Last Demand to CSV");
    analyticsStatusLabel = new QLabel();

    analyticsLayout->addWidget(btnShowDemand);
    analyticsLayout->addWidget(btnShowAreaTrends);
    analyticsLayout->addWidget(btnExportCSV);
    analyticsLayout->addWidget(analyticsStatusLabel);
    analyticsTab->setLayout(analyticsLayout);
    tabWidget->addTab(analyticsTab, "Analytics");

    connect(btnShowDemand, &QPushButton::clicked, this, &GUIManager::onShowDemandClicked);
    connect(btnShowAreaTrends, &QPushButton::clicked, this, &GUIManager::onShowAreaTrendsClicked);
    connect(btnExportCSV, &QPushButton::clicked, this, &GUIManager::onExportDemandCSV);

    setWindowTitle("BloodLife - Qt GUI");
    resize(900, 700);
}

///// Helper to populate QTableWidget from vector<vector<string>>
void GUIManager::populateTable(const std::vector<std::vector<std::string>>& rows,
                               const std::vector<std::string>& headers) {
    tableResults->clear();
    if (!headers.empty()) {
        tableResults->setColumnCount(static_cast<int>(headers.size()));
        QStringList qheaders;
        for (auto& h : headers) qheaders << QString::fromStdString(h);
        tableResults->setHorizontalHeaderLabels(qheaders);
    } else {
        // keep existing header count
    }

    tableResults->setRowCount(static_cast<int>(rows.size()));
    for (int r = 0; r < static_cast<int>(rows.size()); ++r) {
        const auto& row = rows[r];
        tableResults->setRowCount(r + 1);
        tableResults->setColumnCount(static_cast<int>(row.size()));
        for (int c = 0; c < static_cast<int>(row.size()); ++c) {
            tableResults->setItem(r, c, new QTableWidgetItem(QString::fromStdString(row[c])));
        }
    }
    tableResults->resizeColumnsToContents();
}

///// Slots

void GUIManager::onRegisterDonorClicked() {
    // Basic validation
    std::string name = leName->text().toStdString();
    int age = leAge->text().toInt();
    std::string gender = cbGender->currentText().toStdString();
    std::string phone = lePhone->text().toStdString();
    std::string city = leCity->text().toStdString();
    std::string address = leAddress->text().toStdString();
    std::string blood = cbBloodGroup->currentText().toStdString();
    bool ht = (cbHealthTest->currentText().toStdString() == "1");

    if (name.empty() || phone.empty() || city.empty()) {
        QMessageBox::warning(this, "Validation", "Please fill name, phone and city.");
        return;
    }

    Donor d;
    if (d.registerDonor(db, name, age, gender, phone, city, address, blood, ht)) {
        donorStatusLabel->setText("Donor registration submitted.");
        // clear inputs
        leName->clear(); leAge->clear(); lePhone->clear(); leCity->clear(); leAddress->clear();
    } else {
        donorStatusLabel->setText("Registration failed.");
    }
}

void GUIManager::onApproveDonorClicked() {
    std::string phone = leAdminPhone->text().toStdString();
    if (phone.empty()) {
        QMessageBox::warning(this, "Validation", "Enter donor phone.");
        return;
    }
    Admin admin;
    admin.approveDonor(db, phone);
    adminStatusLabel->setText("Approve command sent.");
}

void GUIManager::onRejectDonorClicked() {
    std::string phone = leAdminPhone->text().toStdString();
    std::string reason = leRejectReason->text().toStdString();
    if (phone.empty() || reason.empty()) {
        QMessageBox::warning(this, "Validation", "Enter phone and rejection reason.");
        return;
    }
    Admin admin;
    admin.rejectDonor(db, phone, reason);
    adminStatusLabel->setText("Reject command sent.");
}

void GUIManager::onHospitalSearchClicked() {
    std::string bg = leSearchBlood->text().toStdString();
    std::string city = leSearchCity->text().toStdString();
    if (bg.empty() || city.empty()) {
        QMessageBox::warning(this, "Validation", "Enter blood group and city.");
        return;
    }

    // Use Search class to execute
    Search s;
    int count = s.executeSearch(db, bg, city);

    // Populate tableResults with s.getResults()
    populateTable(s.getResults(), { "Name", "Phone", "City", "Blood Group" });
}

void GUIManager::onSaveSearchClicked() {
    std::string area = leHospitalArea->text().toStdString();
    std::string bg = leSearchBlood->text().toStdString();
    if (area.empty() || bg.empty()) {
        QMessageBox::warning(this, "Validation", "Run a search and provide an area.");
        return;
    }
    int hospitalID = 1; // demo fixed id
    if (SearchLog::logSearch(db, hospitalID, bg, area)) {
        QMessageBox::information(this, "Saved", "Search saved to log.");
    } else {
        QMessageBox::warning(this, "Error", "Could not save search.");
    }
}

void GUIManager::onShowDemandClicked() {
    auto rows = Analytics::showDemandByBloodGroup(db);
    auto headers = Analytics::demandByBloodGroupHeaders();
    populateTable(rows, headers);
    analyticsStatusLabel->setText("Demand loaded.");
}

void GUIManager::onShowAreaTrendsClicked() {
    auto rows = Analytics::showAreaWiseTrends(db);
    auto headers = Analytics::areaWiseTrendsHeaders();
    populateTable(rows, headers);
    analyticsStatusLabel->setText("Area trends loaded.");
}

void GUIManager::onExportDemandCSV() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    auto rows = Analytics::showDemandByBloodGroup(db);
    auto headers = Analytics::demandByBloodGroupHeaders();
    bool ok = Analytics::exportResultsToCSV(fileName.toStdString(), headers, rows);
    if (ok) QMessageBox::information(this, "Export", "CSV exported successfully.");
    else QMessageBox::warning(this, "Export", "CSV export failed.");
}
