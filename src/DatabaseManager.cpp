#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    conn = mysql_init(0);
    connected = false;
}

DatabaseManager::~DatabaseManager() {
    if (connected)
        closeConnection();
}

bool DatabaseManager::connectDB(string host, string user, string pass, string db, unsigned int port) {
    conn = mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db.c_str(), port, NULL, 0);
    if (conn) {
        connected = true;
        cout << "✅ Connected to MySQL Database successfully!\n";
        return true;
    } else {
        cout << "❌ Connection failed: " << mysql_error(conn) << endl;
        return false;
    }
}

void DatabaseManager::closeConnection() {
    mysql_close(conn);
    connected = false;
    cout << "🔒 Database connection closed.\n";
}

bool DatabaseManager::executeQuery(const string& query) {
    if (!connected) {
        cout << "⚠️ No active connection!\n";
        return false;
    }
    if (mysql_query(conn, query.c_str())) {
        cout << "❌ Query failed: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

vector<vector<string>> DatabaseManager::fetchResults(const string& query) {
    vector<vector<string>> results;
    if (!connected) return results;

    if (mysql_query(conn, query.c_str())) {
        cout << "❌ Query failed: " << mysql_error(conn) << endl;
        return results;
    }

    res = mysql_store_result(conn);
    int fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        vector<string> r;
        for (int i = 0; i < fields; i++)
            r.push_back(row[i] ? row[i] : "NULL");
        results.push_back(r);
    }
    mysql_free_result(res);
    return results;
}

bool DatabaseManager::isConnected() const { return connected; }

