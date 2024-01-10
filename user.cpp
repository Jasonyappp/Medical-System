#include "user.h"
#include <iostream>



// Function to register a new user
int registerUser(sqlite3 *db, const string &USERNAME, const string &PASSWORD, const string &ROLE) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO USERS (USERNAME, PASSWORD, ROLE) VALUES ('" + USERNAME + "', '" + PASSWORD + "', '" + ROLE + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error registering user: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    return result;
}

// Function to authenticate a user
bool authenticateUser(sqlite3 *db, const string &USERNAME, const string &PASSWORD, const string &ROLE) {
    sqlite3_stmt *stmt;
    string query = "SELECT * FROM USERS WHERE USERNAME='" + USERNAME + "' AND PASSWORD='" + PASSWORD + "' AND ROLE='" + ROLE + "';";

    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    result = sqlite3_step(stmt);

    bool isAuthenticated = (result == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return isAuthenticated;
}