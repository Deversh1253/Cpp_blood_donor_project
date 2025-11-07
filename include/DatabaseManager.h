#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DatabaseManager {
private:
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    bool connected;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connectDB(string host = "localhost",
                   string user = "root",
                   string pass = "root123",
                   string db = "blood_life_db",
                   unsigned int port = 3306);
    void closeConnection();

    bool executeQuery(const string& query);
    vector<vector<string>> fetchResults(const string& query);

    bool isConnected() const;
};

