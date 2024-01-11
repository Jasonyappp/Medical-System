#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "doctor.h"
using namespace std;

Doctor* doctorLogin() {
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


// Function to create a new medical record
int createMedicalRecord(sqlite3 *db, const string &PATIENT_NAME, const string &DIAGNOSIS, const string &ADDMISSION_STATUS, const string &CURRENT_MEDICATION, const string &MEDICATION_DOSAGE, const string &MR_DATE) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO MEDICAL_RECORD (PATIENT_NAME, DIAGNOSIS, ADDMISSION_STATUS, CURRENT_MEDICATION, MEDICATION_DOSAGE, MR_DATE) VALUES ('" + PATIENT_NAME + "', '" + DIAGNOSIS + "', '" + ADDMISSION_STATUS + "', '" + CURRENT_MEDICATION + "', '" + MEDICATION_DOSAGE + "', '" + MR_DATE + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating medical record: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    return result;
}

int deleteMedicalRecord(sqlite3* db, int MR_ID) {
    // Delete records based on MR_ID
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM MEDICAL_RECORD WHERE MR_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, MR_ID);
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

void displayMedical_Record(sqlite3* db, int MR_ID) {
    string query = "SELECT * FROM MEDICAL_RECORD WHERE MR_ID = " + to_string(MR_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }
}


// Function to create a new lab record
int createLabRecord(sqlite3 *db, const string &P_NAME, const string &BLOOD_PRESSURE, const string &HEART_RATE, const string &BLOOD_SUGAR, const string &XRAY, const string &LR_DATE) {
    char *errMsg = nullptr;
    string insert = "INSERT INTO LAB_RECORD (PATIENT_NAME, BLOOD_PRESSURE, HEART_RATE, BLOOD_SUGAR, XRAY, LR_DATE) VALUES ('" + P_NAME + "', '" + BLOOD_PRESSURE + "', '" + HEART_RATE + "', '" + BLOOD_SUGAR + "', '" + XRAY + "', '" + LR_DATE + "');";

    int result = sqlite3_exec(db, insert.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error creating lab record: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    return result;
}

int deleteLabRecord(sqlite3* db, int LR_ID) {
    sqlite3_stmt* stmt;
    string sql = "DELETE FROM LAB_RECORD WHERE LR_ID = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (result != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, LR_ID);
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

void displayLab_Record(sqlite3* db, int LR_ID) {
    string query = "SELECT * FROM LAB_RECORD WHERE LR_ID = " + to_string(LR_ID) + ";";
    int rc = sqlite3_exec(db, query.c_str(), callback, 0, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        }
}