#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
#include "sqlite3.h"
using namespace std;

class Doctor {
public:
    int doctorID;
    string doctorName;
    string role;

    Doctor(int id, string name, string r) : doctorID(id), doctorName(name), role(r) {}
};
Doctor* doctorLogin();
static int callback(void* data, int argc, char** argv, char** azColName);

int createMedicalRecord(sqlite3* db, const string& PATIENT_NAME, const string& DIAGNOSIS, const string& ADDMISSION_STATUS, const string& CURRENT_MEDICATION, const string& MEDICATION_DOSAGE, const string& MR_DATE);
struct MedicalRecord {
    int MR_ID;
    string PATIENT_NAME,DIAGNOSIS,ADDMISSION_STATUS,CURRENT_MEDICATION,MEDICATION_DOSAGE,MR_DATE;

    MedicalRecord* next; // Pointer to the next node in the linked list
};
class MedicalRecordList {
private:
    MedicalRecord* head; // Pointer to the head of the linked list

public:
    MedicalRecordList() : head(nullptr) {}

    // Function to insert a new medical record into the linked list
    void insertMedicalRecord(int MR_ID, const string& PATIENT_NAME, const string& DIAGNOSIS, const string& ADDMISSION_STATUS, const string& CURRENT_MEDICATION, const string& MEDICATION_DOSAGE, const string& MR_DATE) {
        MedicalRecord* newRecord = new MedicalRecord{MR_ID, PATIENT_NAME, DIAGNOSIS, ADDMISSION_STATUS, CURRENT_MEDICATION, MEDICATION_DOSAGE, MR_DATE, nullptr};

        if (head == nullptr) {
            // If the list is empty, set the new record as the head
            head = newRecord;
        } else {
            // Otherwise, insert the new record at the beginning of the list
            newRecord->next = head;
            head = newRecord;
        }
    }
        
    // Function to read and display all medical records in the linked list
        void readMedicalRecords(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM MEDICAL_RECORD;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertMedicalRecord(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadMedicalRecords() {
        MedicalRecord* current = head;

        while (current != nullptr) {
            // Display the information of the current medical record
            cout << "\nMedical Record Id: " << current->MR_ID
                 << "\nPatient Name: " << current->PATIENT_NAME
                 << "\nDiagnosis: " << current->DIAGNOSIS
                 << "\nAdmission Status: " << current->ADDMISSION_STATUS
                 << "\nCurrent Medication: " << current->CURRENT_MEDICATION
                 << "\nMedication Dosage: " << current->MEDICATION_DOSAGE
                 << "\nMedical Record Date: " << current->MR_DATE << endl;

            // Move to the next record in the listz
            current = current->next;
        }
    }
};
int deleteMedicalRecord(sqlite3* db, int MR_ID);
void displayMedical_Record(sqlite3* db, int MR_ID);


int createLabRecord(sqlite3 *db, const string &P_NAME, const string &BLOOD_PRESSURE, const string &HEART_RATE, const string &BLOOD_SUGAR, const string &XRAY, const string &LR_DATE);
struct LabRecord {
    int LR_ID;
    string P_NAME,BLOOD_PRESSURE,HEART_RATE,BLOOD_SUGAR,XRAY,LR_DATE;

    LabRecord* next;
};
class LabRecordList {
private:
    LabRecord* head; 
public:
    LabRecordList() : head(nullptr) {}
    void insertLabRecord(int LR_ID, const string& P_NAME, const string &BLOOD_PRESSURE, const string &HEART_RATE, const string &BLOOD_SUGAR, const string &XRAY, const string &LR_DATE) {
        LabRecord* newRecord = new LabRecord{LR_ID, P_NAME, BLOOD_PRESSURE, HEART_RATE, BLOOD_SUGAR, XRAY, LR_DATE, nullptr};
        if (head == nullptr) {
            head = newRecord;
        } else {
            newRecord->next = head;
            head = newRecord;
        }
    }
        void readLabRecords(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM LAB_RECORD;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertLabRecord(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadLabRecords() {
        LabRecord* current = head;

        while (current != nullptr) {

            cout << "\nLab Record Id: " << current->LR_ID
                 << "\nPatient Name: " << current->P_NAME
                 << "\nBlood Pressure: " << current->BLOOD_PRESSURE
                 << "\nHeart Rate: " << current->HEART_RATE
                 << "\nBlood Sugar: " << current->BLOOD_SUGAR
                 << "\nXray: " << current->XRAY
                 << "\nLab Record Date: " << current->LR_DATE << endl;

            current = current->next;
        }
    }
};
int deleteLabRecord(sqlite3* db, int LR_ID);
void displayLab_Record(sqlite3* db, int LR_ID);

#endif
