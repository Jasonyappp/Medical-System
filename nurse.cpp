#include <iostream>
#include <string>
#include "sqlite3.h"
#include "nurse.h"
using namespace std;

Nurse* nurseLogin() {
    cout << "Welcome !" << endl;
    return nullptr;
}

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


// Function to create a new drugs details
int createDrugsDetails(sqlite3 *db, const string &DRUGS_NAME, int DRUGS_QUANTITY, const string &DRUGS_PDATE, const string &DRUGS_EXPDATE) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO DRUGS_DETAILS(DRUGS_NAME, DRUGS_QUANTITY, DRUGS_PDATE, DRUGS_EXPDATE) VALUES ('" + DRUGS_NAME + "', '" + to_string(DRUGS_QUANTITY) + "', '" + DRUGS_PDATE + "', '" + DRUGS_EXPDATE + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating drugs details: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    return result;
}

int deleteDrugsDetails(sqlite3* db, int DRUGS_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM DRUGS_DETAILS WHERE DRUGS_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, DRUGS_ID);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    cout << "Delete successful!" << endl;
    return 0;
}

void displayDrugsDetails(sqlite3* db, int DRUGS_ID) {
    string query = "SELECT * FROM DRUGS_DETAILS WHERE DRUGS_ID = " + to_string(DRUGS_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}


// Function to create a new equipment details
int createEquipmentDetails(sqlite3 *db, const string &ITEM_NAME, const string &ITEM_CATERGORY, int ITEM_QUANTITY, const string &ITEM_PDATE, const string &ITEM_COST) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO EQUIPMENT_DETAILS(ITEM_NAME, ITEM_CATERGORY, ITEM_QUANTITY, ITEM_PDATE, ITEM_COST) VALUES ('" + ITEM_NAME + "', '" + ITEM_CATERGORY + "', '" + to_string(ITEM_QUANTITY) + "', '" + ITEM_PDATE + "', '" + ITEM_COST + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating equipment details: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    return result;
}

int deleteEquipmentDetails(sqlite3* db, int EQUIPDETAILS_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM EQUIPMENT_DETAILS WHERE EQUIPDETAILS_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, EQUIPDETAILS_ID);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    cout << "Delete successful!" << endl;
    return 0;
}

void displayEquipmentDetails(sqlite3* db, int EQUIPDETAILS_ID) {
    string query = "SELECT * FROM EQUIPMENT_DETAILS WHERE EQUIPDETAILS_ID = " + to_string(EQUIPDETAILS_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}


// Function to create a new inventory details 
int createInventoryDetails(sqlite3 *db, int I_QUANTITY, const string &I_NAME, const string &I_CATERGORY, const string &I_PDATE, const string &I_EXPDATE) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO INVENTORY_DETAILS(ITEM_NAME, ITEM_CATERGORY, ITEM_QUANTITY, ITEM_PDATE, ITEM_EXPDATE) VALUES ('" + I_NAME + "', '" + I_CATERGORY + "', '" + to_string(I_QUANTITY) + "', '" + I_PDATE + "', '" + I_EXPDATE + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating inventory details: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return result;
}

int deleteInventoryDetails(sqlite3* db, int INTDETAILS_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM INVENTORY_DETAILS WHERE INTDETAILS_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, INTDETAILS_ID);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    cout << "Delete successful!" << endl;
    return 0;
}

void displayInventoryDetails(sqlite3* db, int INTDETAILS_ID) {
    string query = "SELECT * FROM INVENTORY_DETAILS WHERE INTDETAILS_ID = " + to_string(INTDETAILS_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}


// Function to create a new on call
int createOnCall(sqlite3 *db, int BLOCK_FLOOR, const string &ROOM_NAME, const string &ON_CALL_START, const string &ON_CALL_END) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO ON_CALL(BLOCK_FLOOR, ROOM_NAME, ON_CALL_START, ON_CALL_END) VALUES ('" + to_string(BLOCK_FLOOR) + "', '" + ROOM_NAME + "', '" + ON_CALL_START + "', '" + ON_CALL_END + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating on call: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return result;
}

int deleteOnCall(sqlite3* db, int ONCALL_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM ON_CALL WHERE ONCALL_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, ONCALL_ID);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    cout << "Delete successful!" << endl;
    return 0;
}

void displayOnCall(sqlite3* db, int ONCALL_ID) {
    string query = "SELECT * FROM ON_CALL WHERE ONCALL_ID = " + to_string(ONCALL_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}


// Function to create a new visit details
int createVisitDetails(sqlite3 *db, int ROOM_ID, const string &VISITOR_NAME, const string &VISIT_DURATION, const string &VISIT_DATE, const string &RELATIONSHIP) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO VISIT_DETAILS(ROOM_ID, VISITOR_NAME, VISIT_DURATION, VISIT_DATE, RELATIONSHIP) VALUES ('" + to_string(ROOM_ID) + "', '" + VISITOR_NAME + "', '" + VISIT_DURATION + "', '" + VISIT_DATE + "', '" + RELATIONSHIP + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating visit details: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return result;
}

int deleteVisitDetails(sqlite3* db, int VISIT_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM VISIT_DETAILS WHERE VISIT_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, VISIT_ID);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    cout << "Delete successful!" << endl;
    return 0;
}

void displayVisitDetails(sqlite3* db, int VISIT_ID) {
    string query = "SELECT * FROM VISIT_DETAILS WHERE VISIT_ID = " + to_string(VISIT_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}
