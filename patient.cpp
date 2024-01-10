#include "patient.h"
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
using namespace std;

// Implement the member functions here

Patient* patientLogin() {
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

void displayInvoice(sqlite3* db, int PAYMENT_ID) {
    string query = "SELECT * FROM PAYMENT WHERE PAYMENT_ID = " + to_string(PAYMENT_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }
}

void displayAppointment(sqlite3* db, int APPOINT_ID) {
    string query = "SELECT * FROM APPOINTMENT WHERE APPOINT_ID = " + to_string(APPOINT_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}

