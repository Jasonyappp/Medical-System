#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"
#include "patient.h"
#include "doctor.h"
#include "user.h"
#include "nurse.h"
using namespace std;

int main(int argc, char** argv) {
    vector<Patient> patients;
    Patient* loggedInPatient = patientLogin();

    while (true) {
        cout << "*************************************************" << endl;
        cout << "*        Hospital Management System Login       *" << endl;
        cout << "*************************************************" << endl;
        cout << "*               1. Patient                      *" << endl;
        cout << "*               2. Doctor & Nurse               *" << endl;
        cout << "*               3. Sign Up                      *" << endl;
        cout << "*               4. Exit                         *" << endl;
        cout << "*************************************************" << endl;

        int choice;
        cin >> choice;
        //patient
        if (choice == 1) {
            Patient* loggedInPatient = patientLogin();
            while (true) {
                cout << "*************************************************" << endl;
                cout << "*                 Patient                       *" << endl;                
                cout << "*************************************************" << endl;
                cout << "*              1. Payment                       *" << endl;
                cout << "*              2. Make Appointment              *" << endl;
                cout << "*              3. Back                          *" << endl;
                cout << "*************************************************" << endl;

                int choice;
                cin >> choice;

                // Payment
                if (choice == 1) {
                    string PAYMENT_METHOD, PAYMENT_STATUS, PAYMENT_DATE;
                    double AMOUNT;
                    int PAYMENT_ID;
                    
                        sqlite3* DB;
                        int exit = sqlite3_open("hospital.db", &DB);

                        if (exit) {
                            cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
                            return (-1);
                        }

                        // Prompt the user for input
                        cout << "Enter Payment Date (DD-MM-YYYY): ";
                        cin >> ws;
                        getline(cin, PAYMENT_DATE);
                        cout << "Enter Payment Method (Credit Card, Cash, TNG): ";
                        getline(cin, PAYMENT_METHOD);
                        cout << "Enter Payment Status (Pay, Unpay): ";
                        getline(cin, PAYMENT_STATUS);
                        cout << "Enter your payment amount: ";
                        cin >> AMOUNT;
                        cin.ignore();
                        cout << endl;

                        do{
                            cout << "Confirm ? (1. Yes / 2. NO): ";
                            int choice;
                            cin >> choice;

                            if (choice == 1){
                                sqlite3_stmt* stmt;
                                string sql = "INSERT INTO PAYMENT (PAYMENT_DATE, PAYMENT_STATUS, PAYMENT_METHOD, AMOUNT) VALUES (?, ?, ?, ?);";

                                exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

                                if (exit != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
                                    sqlite3_close(DB);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, PAYMENT_DATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_text(stmt, 2, PAYMENT_STATUS.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_text(stmt, 3, PAYMENT_METHOD.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_double(stmt, 4, AMOUNT);

                                // Execute the statement
                                exit = sqlite3_step(stmt);

                                if (exit != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(DB) << endl;
                                    sqlite3_close(DB);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);
                                cout << "Record created successfully!" << endl;
                                
                                
                                    int lastInsertedPaymentId = sqlite3_last_insert_rowid(DB);

                                    displayInvoice(DB, lastInsertedPaymentId);

                                    sqlite3_close(DB);

                                    return 0;
                            
                                    }else if (choice == 2) { //BACK
                                        cout << "Please Try Again." << endl;
                                        cout << endl;
                                    // Go back to the previous menu
                                    } else {
                                        cout << "Invalid choice." << endl;
                                        cout << endl;
                                    }
                         } while (choice != 1 && choice != 2); 
                // Make Appointment
                }else if (choice == 2) {

                        cout <<"********************************************"<< endl;
                        cout <<"*                 Dr.Jason                 *"<< endl;
                        cout <<"*                Orthopedist               *"<< endl;
                        cout <<"*               Monday-Sunday              *"<< endl;
                        cout <<"********************************************"<< endl;
                        cout << endl;
                        cout <<"********************************************"<< endl;
                        cout <<"*                 Dr.Wilson                *"<< endl;
                        cout <<"*              Cardiopulmonary             *"<< endl;
                        cout <<"*               Monday-Sunday              *"<< endl;
                        cout <<"********************************************"<< endl;
                        cout << endl;
                        cout <<"********************************************"<< endl;
                        cout <<"*                 Dr.Aiting                *"<< endl;
                        cout <<"*       Obstetrician and Gynecologist      *"<< endl;
                        cout <<"*               Monday-Sunday              *"<< endl;
                        cout <<"********************************************"<< endl;
                        cout << endl;

                        string APPOINT_DOCTOR, APPOINT_SPECIALTY, APPOINT_DATETIME; //doctor appointment

                        sqlite3* DB;
                        int exit = sqlite3_open("hospital.db", &DB);

                        if (exit) {
                            cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
                            return (-1);
                        }

                        cout << "Enter your preferred doctor: ";
                        cin >> ws ;
                        getline(cin, APPOINT_DOCTOR);
                        cout << "Enter the specialty: ";
                        getline(cin, APPOINT_SPECIALTY);
                        cout << "Enter your preferred date/time (DD-MM-YYYY HH:MM am/pm): ";
                        getline(cin, APPOINT_DATETIME);

                        do{
                            cout << "Confirm ? (1. Yes / 2. NO): ";
                            int choice;
                            cin >> choice;

                            if (choice == 1){
                                sqlite3_stmt* stmt;
                                string sql = "INSERT INTO APPOINTMENT (APPOINT_DOCTOR, APPOINT_SPECIALTY, APPOINT_DATETIME) VALUES (?, ?, ?);";
                               

                                exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

                                if (exit != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
                                    sqlite3_close(DB);
                                    return (-1);
                                }

                                
                                sqlite3_bind_text(stmt, 1, APPOINT_DOCTOR.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_text(stmt, 2, APPOINT_SPECIALTY.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_text(stmt, 3, APPOINT_DATETIME.c_str(), -1, SQLITE_STATIC);

                                // Execute the statement
                                exit = sqlite3_step(stmt);

                                if (exit != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(DB) << endl;
                                    sqlite3_close(DB);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);
                                
                                cout << "Record created successfully!" << endl;
                                
                                
                                    int lastInsertedAppointId = sqlite3_last_insert_rowid(DB);
                                    displayAppointment(DB, lastInsertedAppointId);
                                    sqlite3_close(DB);

                                    return 0;                                
                                    continue;
                                    }else if (choice == 2) { //BACK
                                    cout << "Please Try Again." << endl;
                                    // Go back to the previous menu
                                    } else {
                                    cout << "Invalid choice." << endl;
                                    }
                                    } while (choice != 1 && choice != 2); // Repeat the loop until a valid choice is made     
                //Back
                }else if(choice == 3){
                    break;
                }
            }
        }

        //doctor&nurse
        else if (choice == 2) {
            
            sqlite3 *db;
            int result = sqlite3_open("hospital.db", &db);

            if (result != SQLITE_OK) {
                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                return result;
            }

            bool loggedIn = false;
            int loggout;
            string USERNAME, PASSWORD, ROLE;

            while (!loggedIn) { 
            
                cout << "Enter your username: ";
                cin >> USERNAME;
                cout << "Enter your password: ";
                cin >> PASSWORD;
                cout << "Enter your role (doctor/nurse): ";
                cin >> ROLE;
                    
                cin.sync();

                loggedIn = authenticateUser(db, USERNAME, PASSWORD, ROLE);

                if (loggedIn) {
                    cout << "Login successful!" << endl;
                } else {
                    cout << "Login failed. Please try again." << endl;
                }     
                
            
                while (loggedIn && ROLE == "doctor"){ //doctor
                    cout << "*************************************************" << endl;
                    cout << "*                   Welcome !                   *" << endl;
                    cout << "*************************************************" << endl;
                    cout << "*              1. Medical Record                *" << endl;
                    cout << "*              2. Lab Record                    *" << endl;
                    cout << "*              3. Logout                        *" << endl;
                    cout << "*************************************************" << endl;
                    cin >> choice;
                        
                    if (choice == 1){ //medical record
                    
                        cout << "*************************************************" << endl;
                        cout << "*                 Medical Record                *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int mrChoice, MR_ID;
                        cin >> mrChoice;
                        string PATIENT_NAME,DIAGNOSIS,ADDMISSION_STATUS,CURRENT_MEDICATION,MEDICATION_DOSAGE,MR_DATE;

                        if (mrChoice == 1){ //create

                            cout << "Enter Patient Name: ";
                            cin >> PATIENT_NAME;
                            cout << "Enter Diagnosis: ";
                            cin >> DIAGNOSIS;
                            cout << "Enter Addmisson Status(Y/N): ";
                            cin >> ADDMISSION_STATUS;
                            cout << "Enter Current Medication Name: ";
                            cin >> CURRENT_MEDICATION;
                            cout << "Enter Dosage: ";
                            cin >> MEDICATION_DOSAGE;
                            cout << "Enter Medical Record Date(DD-MM-YYYY HH:MMam/pm): ";
                            cin >> MR_DATE;

                            result = createMedicalRecord(db, PATIENT_NAME, DIAGNOSIS, ADDMISSION_STATUS, CURRENT_MEDICATION, MEDICATION_DOSAGE, MR_DATE);

                                if (result == SQLITE_OK) {
                                    cout << "\nMedical record created successfully!" << endl;
                                    int lastInsertedMRId = sqlite3_last_insert_rowid(db);
                                    displayMedical_Record(db, lastInsertedMRId);
                                    sqlite3_close(db);
                                    continue;
                                } else {
                                    cout << "Error creating medical record. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(mrChoice == 2){ //read  
                            MedicalRecordList medicalRecordList;

                            medicalRecordList.readMedicalRecords(db);

                            medicalRecordList.displayreadMedicalRecords();

                        return 0;
                        
                        }else if(mrChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*              Update                *" << endl;
                            cout << "**************************************" << endl;
                            cout << "*       1. Patient Name              *" << endl;
                            cout << "*       2. Diagnosis                 *" << endl;
                            cout << "*       3. Addmission Status         *" << endl;
                            cout << "*       4. Current Medication        *" << endl;
                            cout << "*       5. Medication Dosage         *" << endl;
                            cout << "*       6. Medical Record Date       *" << endl;
                            cout << "*       7. Back to Main Menu         *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit patient name
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new patient name: ";
                                cin >> PATIENT_NAME;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE MEDICAL_RECORD SET PATIENT_NAME = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, PATIENT_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt, 2, MR_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;

                            }else if(editChoice == 2){ //edit diagnosis

                            sqlite3* db;
                            int exit = sqlite3_open("hospital.db", &db);
                                 
                                if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new diagnosis: ";
                                cin >> DIAGNOSIS;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt1;  
                                string sql1 = "UPDATE MEDICAL_RECORD SET DIAGNOSIS = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, DIAGNOSIS.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, MR_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;

                            }else if(editChoice == 3){ //edit Addmission Status
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new Addmission Status: ";
                                cin >> ADDMISSION_STATUS;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt2;  
                                string sql2 = "UPDATE MEDICAL_RECORD SET ADDMISSION_STATUS = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt2, 1, ADDMISSION_STATUS.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt2, 2, MR_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;

                            }else if(editChoice == 4){ //edit Current Medication
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new current medication: ";
                                cin >> CURRENT_MEDICATION;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE MEDICAL_RECORD SET CURRENT_MEDICATION = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, CURRENT_MEDICATION.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, MR_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;
                            }else if(editChoice == 5){ //edit Dosage
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new medication dosage: ";
                                cin >> MEDICATION_DOSAGE;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt4;  
                                string sql4 = "UPDATE MEDICAL_RECORD SET MEDICATION_DOSAGE = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql4.c_str(), -1, &stmt4, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt4, 1, MEDICATION_DOSAGE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt4, 2, MR_ID);

                                result = sqlite3_step(stmt4);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt4);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;

                            }else if(editChoice == 6){ //edit Date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new date: ";
                                cin >> MR_DATE;
                                cout << "Enter medical record ID: ";
                                cin >> MR_ID;

                                sqlite3_stmt* stmt5;  
                                string sql5 = "UPDATE MEDICAL_RECORD SET MR_DATE = ? WHERE MR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql5.c_str(), -1, &stmt5, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt5, 1, MR_DATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt5, 2, MR_ID);

                                result = sqlite3_step(stmt5);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt5);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                continue;
                            }else{ //back
                                break;
                            }
                        
                        }else if(mrChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the medical record id to delete: ";
                            cin >> MR_ID;
                            result = deleteMedicalRecord(db, MR_ID);

                            if (result != 0) {
                                cerr << "Failed to delete medical record." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if (mrChoice == 5){ //back
                        }else { //back  
                        break;                        
                        }
          
                    }else if (choice == 2) { //lab record  
                        cout << "*************************************************" << endl;
                        cout << "*                   Lab Record                  *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int lrChoice, LR_ID;
                        cin >> lrChoice;
                        string P_NAME,BLOOD_PRESSURE,HEART_RATE,BLOOD_SUGAR,XRAY,LR_DATE;

                        if (lrChoice == 1){ //create

                            cout << "Enter Patient Name: ";
                            cin >> P_NAME;
                            cout << "Enter Patient Blood Pressure: ";
                            cin >> BLOOD_PRESSURE;
                            cout << "Enter Patient Heart Rate: ";
                            cin >> HEART_RATE;
                            cout << "Enter Patient Blood Sugar: ";
                            cin >> BLOOD_SUGAR;
                            cout << "Enter Patient Xray Description: ";
                            cin >> XRAY;
                            cout << "Enter Record Date(DD-MM-YYYY HH:MMam/pm): ";
                            cin >> LR_DATE;

                            result = createLabRecord(db, P_NAME, BLOOD_PRESSURE,HEART_RATE,BLOOD_SUGAR,XRAY,LR_DATE);

                                if (result == SQLITE_OK) {
                                    cout << "\nLab record created successfully!" << endl;
                                    int lastInsertedLRId = sqlite3_last_insert_rowid(db);
                                    displayLab_Record(db, lastInsertedLRId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating lab record. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(lrChoice == 2){ //read  
                            LabRecordList LabRecordList;
                            LabRecordList.readLabRecords(db);
                            LabRecordList.displayreadLabRecords();

                        return 0;
                        
                        }else if(lrChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*               Update               *" << endl;
                            cout << "**************************************" << endl;
                            cout << "*        1. Patient Name             *" << endl;
                            cout << "*        2. Blood Pressure           *" << endl;
                            cout << "*        3. Heart Rate               *" << endl;
                            cout << "*        4. Blood Sugar              *" << endl;
                            cout << "*        5. Xray                     *" << endl;
                            cout << "*        6. Lab Record Date          *" << endl;
                            cout << "*        7. Back to Main Menu        *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit patient name
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new patient name: ";
                                cin >> P_NAME;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE LAB_RECORD SET PATIENT_NAME = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, P_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt, 2, LR_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit BLOOD PRESSURE
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new blood pressure: ";
                                cin >> BLOOD_PRESSURE;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt1;  
                                string sql1 = "UPDATE LAB_RECORD SET BLOOD_PRESSURE = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, BLOOD_PRESSURE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, LR_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit HEART_RATE
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new heart rate: ";
                                cin >> HEART_RATE;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt2; 
                                string sql2 = "UPDATE LAB_RECORD SET HEART_RATE = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt2, 1, HEART_RATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt2, 2, LR_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit BLOOD_SUGAR
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new blood sugar: ";
                                cin >> BLOOD_SUGAR;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE LAB_RECORD SET BLOOD_SUGAR = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, BLOOD_SUGAR.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, LR_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else if(editChoice == 5){ //edit XRAY
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new xray description: ";
                                cin >> XRAY;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt4;  
                                string sql4 = "UPDATE LAB_RECORD SET XRAY = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql4.c_str(), -1, &stmt4, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt4, 1, XRAY.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt4, 2, LR_ID);

                                result = sqlite3_step(stmt4);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt4);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 6){ //edit LR_DATE
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new lab record date: ";
                                cin >> LR_DATE;
                                cout << "Enter lab record ID: ";
                                cin >> LR_ID;

                                sqlite3_stmt* stmt5;  
                                string sql5 = "UPDATE LAB_RECORD SET LR_DATE = ? WHERE LR_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql5.c_str(), -1, &stmt5, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt5, 1, LR_DATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt5, 2, LR_ID);

                                result = sqlite3_step(stmt5);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt5);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else{ //back
                                break;
                            }
                        
                        }else if(lrChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the lab record id to delete: ";
                            cin >> LR_ID;
                            result = deleteLabRecord(db, LR_ID);

                            if (result != 0) {
                                cerr << "Failed to delete lab record." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(lrChoice == 5){ //back
                            break;
                        }else{                        
                        }
                    }else if (choice == 3){ //logout
                        cout << "Logging out..." << endl;
                        if (loggout != 3) {
                                    cout << "\nLogout successfully!" << endl;
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Logout failed. Please try again." << endl;
                                    return loggout;
                                }
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                    }  
                
             
                while (loggedIn && ROLE == "nurse"){ //nurse
                    cout << "*************************************************" << endl;
                    cout << "*                   Welcome !                   *" << endl;
                    cout << "*************************************************" << endl;
                    cout << "*               1. Drugs Details                *" << endl;
                    cout << "*               2. Equipment Details            *" << endl;
                    cout << "*               3. Inventory Details            *" << endl;
                    cout << "*               4. On Call                      *" << endl;
                    cout << "*               5. Visit Dtails                 *" << endl;
                    cout << "*               6. Logout                       *" << endl;
                    cout << "*************************************************" << endl;
                    cin >> choice;

                    if (choice == 1){ //drugs details
                        cout << "*************************************************" << endl;
                        cout << "*                  Drugs Details                *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int ddChoice, DRUGS_ID, DRUGS_QUANTITY;
                        cin >> ddChoice;
                        string DRUGS_NAME,DRUGS_PDATE,DRUGS_EXPDATE;

                        if (ddChoice == 1){ //create
                            cout << "Enter Drugs Name: ";
                            cin >> DRUGS_NAME;
                            cout << "Enter Drugs Quantity: ";
                            cin >> DRUGS_QUANTITY;
                            cin.ignore();
                            cout << "Enter Purchase Date(DD-MM-YYYY): ";
                            cin >> DRUGS_PDATE;
                            cout << "Enter Expired Date(DD-MM-YYYY): ";
                            cin >> DRUGS_EXPDATE;

                            result = createDrugsDetails(db, DRUGS_NAME, DRUGS_QUANTITY, DRUGS_PDATE, DRUGS_EXPDATE);

                                if (result == SQLITE_OK) {
                                    cout << "\nDrugs Details created successfully!" << endl;
                                    int lastInsertedDrugsId = sqlite3_last_insert_rowid(db);
                                    displayDrugsDetails(db, lastInsertedDrugsId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating Drugs Details. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(ddChoice == 2){ //read  
                            DrugsDetailsList DrugsDetailsList;
                            DrugsDetailsList.readDrugsDetails(db);
                            DrugsDetailsList.displayreadDrugsDetails();

                        return 0;
                        
                        }else if(ddChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*              Update                *" << endl;
                            cout << "**************************************" << endl;
                            cout << "*         1. Drugs Name              *" << endl;
                            cout << "*         2. Drugs Quantity          *" << endl;
                            cout << "*         3. Purchase Date           *" << endl;
                            cout << "*         4. Expired Date            *" << endl;
                            cout << "*         5. Back to Main Menu       *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit Drugs Name
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new drugs name: ";
                                cin >> DRUGS_NAME;
                                cout << "Enter drugs ID: ";
                                cin >> DRUGS_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE DRUGS_DETAILS SET DRUGS_NAME = ? WHERE DRUGS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, DRUGS_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt, 2, DRUGS_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit DRUGS QUANTITY
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new drugs quantity: ";
                                cin >> DRUGS_QUANTITY;
                                cin.ignore();
                                cout << "Enter drugs ID: ";
                                cin >> DRUGS_ID;

                                sqlite3_stmt* stmt1; 
                                string sql1 = "UPDATE DRUGS_DETAILS SET DRUGS_QUANTITY = ? WHERE DRUGS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_int(stmt1, 1, DRUGS_QUANTITY);
                                sqlite3_bind_int(stmt1, 2, DRUGS_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit Purchase Date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new purchase date(DD-MM-YYYY): ";
                                cin >> DRUGS_PDATE;
                                cout << "Enter drugs ID: ";
                                cin >> DRUGS_ID;

                                sqlite3_stmt* stmt2;  
                                string sql2 = "UPDATE DRUGS_DETAILS SET DRUGS_PDATE = ? WHERE DRUGS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt2, 1, DRUGS_PDATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt2, 2, DRUGS_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit Expired date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new expired date: ";
                                cin >> DRUGS_EXPDATE;
                                cout << "Enter drugs ID: ";
                                cin >> DRUGS_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE DRUGS_DETAILS SET DRUGS_EXPDATE = ? WHERE DRUGS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, DRUGS_EXPDATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, DRUGS_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else{ //back
                                break;
                            }
                        
                        }else if(ddChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the drugs id to delete: ";
                            cin >> DRUGS_ID;
                            result = deleteDrugsDetails(db, DRUGS_ID);

                            if (result != 0) {
                                cerr << "Failed to delete drugs details." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(ddChoice == 5){ //back
                            break;
                        }else{ 
                                      
                        }
                    
                    }else if (choice == 2) { //equipment details  
                        cout << "*************************************************" << endl;
                        cout << "*                Equipment Details              *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int edChoice, EQUIPDETAILS_ID, ITEM_QUANTITY;
                        cin >> edChoice;
                        string ITEM_NAME, ITEM_CATERGORY, ITEM_PDATE, ITEM_COST;

                        if (edChoice == 1){ //create

                            cout << "Enter Equipment Name: ";
                            cin >> ITEM_NAME;
                            cout << "Enter Equipment Catergory: ";
                            cin >> ITEM_CATERGORY;
                            cout << "Enter Equipment Quatity: ";
                            cin >> ITEM_QUANTITY;
                            cin.ignore();
                            cout << "Enter Equipment Purchase Date(DD-MM-YYYY): ";
                            cin >> ITEM_PDATE;
                            cout << "Enter Equipment Cost(RM): ";
                            cin >> ITEM_COST;

                            result = createEquipmentDetails(db, ITEM_NAME, ITEM_CATERGORY, ITEM_QUANTITY, ITEM_PDATE, ITEM_COST);

                                if (result == SQLITE_OK) {
                                    cout << "\nEquipment Details created successfully!" << endl;
                                    int lastInsertedEquipDetailsId = sqlite3_last_insert_rowid(db);
                                    displayEquipmentDetails(db, lastInsertedEquipDetailsId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating equipment details. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(edChoice == 2){ //read  
                            EquipDetailsList EquipDetailsList;
                            EquipDetailsList.readEquipDetails(db);
                            EquipDetailsList.displayreadEquipDetails();

                        return 0;
                        
                        }else if(edChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*              Update                *" << endl
                            cout << "**************************************" << endl;
                            cout << "*       1. Equipment Name            *" << endl;
                            cout << "*       2. Equipment Catergory       *" << endl;
                            cout << "*       3. Equipment Quantity        *" << endl;
                            cout << "*       4. Equipment Purchase Date   *" << endl;
                            cout << "*       5. Equipment Cost            *" << endl;
                            cout << "*       6. Back to Main Menu         *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit equipment name
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new equipment name: ";
                                cin >> ITEM_NAME;
                                cout << "Enter equipment id: ";
                                cin >> EQUIPDETAILS_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE EQUIPMENT_DETAILS SET ITEM_NAME = ? WHERE EQUIPDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, ITEM_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt, 2, EQUIPDETAILS_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit equipment catergory
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new equipment catergory: ";
                                cin >> ITEM_CATERGORY;
                                cout << "Enter equipment id: ";
                                cin >> EQUIPDETAILS_ID;

                                sqlite3_stmt* stmt1; 
                                string sql1 = "UPDATE EQUIPMENT_DETAILS SET ITEM_CATERGORY = ? WHERE EQUIPDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, ITEM_CATERGORY.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, EQUIPDETAILS_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit equipment quantity
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new equipment quantity: ";
                                cin >> ITEM_QUANTITY;
                                cin.ignore();
                                cout << "Enter equipment id: ";
                                cin >> EQUIPDETAILS_ID;

                                sqlite3_stmt* stmt2; 
                                string sql2 = "UPDATE EQUIPMENT_DETAILS SET ITEM_QUANTITY = ? WHERE EQUIPDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_int(stmt2, 1, ITEM_QUANTITY);
                                sqlite3_bind_int(stmt2, 2, EQUIPDETAILS_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit Purchase Date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new purchase date(DD-MM-YYYY): ";
                                cin >> ITEM_PDATE;
                                cout << "Enter equipment id: ";
                                cin >> EQUIPDETAILS_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE EQUIPMENT_DETAILS SET ITEM_PDATE = ? WHERE EQUIPDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, ITEM_PDATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, EQUIPDETAILS_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else if(editChoice == 5){ //edit Cost
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new equipment cost(RM): ";
                                cin >> ITEM_COST;
                                cout << "Enter equipment ID: ";
                                cin >> EQUIPDETAILS_ID;

                                sqlite3_stmt* stmt4;  
                                string sql4 = "UPDATE EQUIPMENT_DETAILS SET ITEM_COST = ? WHERE EQUIPDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql4.c_str(), -1, &stmt4, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt4, 1, ITEM_COST.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt4, 2, EQUIPDETAILS_ID);

                                result = sqlite3_step(stmt4);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt4);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 6){ //back
                                break;
                            }else{ 
                                break;
                            }
                        
                        }else if(edChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the equipment id to delete: ";
                            cin >> EQUIPDETAILS_ID;
                            result = deleteEquipmentDetails(db, EQUIPDETAILS_ID);

                            if (result != 0) {
                                cerr << "Failed to delete equipment details." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(edChoice == 5){ //back
                            break;
                        }else{                        
                        }

                    }else if (choice == 3) { //inventory details  
                        cout << "*************************************************" << endl;
                        cout << "*                Inventory Details              *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int idChoice, INTDETAILS_ID, I_QUANTITY;
                        cin >> idChoice;
                        string I_NAME, I_CATERGORY, I_PDATE, I_EXPDATE;

                        if (idChoice == 1){ //create

                            cout << "Enter Item Name: ";
                            cin >> I_NAME;
                            cout << "Enter Item Category: ";
                            cin >> I_CATERGORY;
                            cout << "Enter Item Quantity: ";
                            cin >> I_QUANTITY;
                            cin.ignore();
                            cout << "Enter Purchase Date: ";
                            cin >> I_PDATE;
                            cout << "Enter Expired Date: ";
                            cin >> I_EXPDATE;

                            result = createInventoryDetails(db, I_QUANTITY, I_NAME, I_CATERGORY,I_PDATE,I_EXPDATE);

                                if (result == SQLITE_OK) {
                                    cout << "\nInventory Details created successfully!" << endl
                                    int lastInsertedIntdetailsId = sqlite3_last_insert_rowid(db);
                                    displayInventoryDetails(db, lastInsertedIntdetailsId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating inventory details. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(idChoice == 2){ //read  
                            InventoryDetailsList InventoryDetailsList;
                            InventoryDetailsList.readInventoryDetails(db);
                            InventoryDetailsList.displayreadInventoryDetails();

                        return 0;
                        
                        }else if(idChoice == 3){ //update
                            cout << "************************************" << endl;
                            cout << "*              Update              *" << endl;
                            cout << "************************************" << endl;
                            cout << "*        1. Item Name              *" << endl;
                            cout << "*        2. Item Category          *" << endl;
                            cout << "*        3. Item Quantity          *" << endl;
                            cout << "*        4. Purchase Date          *" << endl;
                            cout << "*        5. Expired Date           *" << endl;
                            cout << "*        6. Back to Main Menu      *" << endl;
                            cout << "************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit Item Name
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new item name: ";
                                cin >> I_NAME;
                                cout << "Enter inventory id: ";
                                cin >> INTDETAILS_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE INVENTORY_DETAILS SET ITEM_NAME = ? WHERE INTDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt, 1, I_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt, 2, INTDETAILS_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit Item Category
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new item catergory: ";
                                cin >> I_CATERGORY;
                                cout << "Enter inventory ID: ";
                                cin >> INTDETAILS_ID;

                                sqlite3_stmt* stmt1;  
                                string sql1 = "UPDATE INVENTORY_DETAILS SET ITEM_CATERGORY = ? WHERE INTDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, I_CATERGORY.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, INTDETAILS_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit Item Quantity
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new item quantity: ";
                                cin >> I_QUANTITY;
                                cin.ignore();
                                cout << "Enter inventory id: ";
                                cin >> INTDETAILS_ID;

                                sqlite3_stmt* stmt2; 
                                string sql2 = "UPDATE INVENTORY_DETAILS SET ITEM_QUANTITY = ? WHERE INTDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_int(stmt2, 1, I_QUANTITY);
                                sqlite3_bind_int(stmt2, 2, INTDETAILS_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit Purchase date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new purchase date: ";
                                cin >> I_PDATE;
                                cout << "Enter inventory id: ";
                                cin >> INTDETAILS_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE INVENTORY_DETAILS SET ITEM_PDATE = ? WHERE INTDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, I_PDATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, INTDETAILS_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else if(editChoice == 5){ //edit expiry date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new expiry date: ";
                                cin >> I_EXPDATE;
                                cout << "Enter inventory ID: ";
                                cin >> INTDETAILS_ID;

                                sqlite3_stmt* stmt4;  
                                string sql4 = "UPDATE INVENTORY_DETAILS SET ITEM_EXPDATE = ? WHERE INTDETAILS_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql4.c_str(), -1, &stmt4, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt4, 1, I_EXPDATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt4, 2, INTDETAILS_ID);

                                result = sqlite3_step(stmt4);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt4);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 6){ //back
                                break;
                            }else{

                            }

                        }else if(idChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the inventory id to delete: ";
                            cin >> INTDETAILS_ID;
                            result = deleteInventoryDetails(db, INTDETAILS_ID);

                            if (result != 0) {
                                cerr << "Failed to delete inventory details." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(idChoice == 5){ //back
                            break;
                        }else{                        
                        }
                    
            
                    }else if (choice == 4) { //On Call  
                        cout << "*************************************************" << endl;
                        cout << "*                    On Call                    *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int ooChoice, ONCALL_ID, BLOCK_FLOOR;
                        cin >> ooChoice;
                        string ROOM_NAME, ON_CALL_START, ON_CALL_END;

                        if (ooChoice == 1){ //create

                            cout << "Enter Block Floor: ";
                            cin >> BLOCK_FLOOR;
                            cin.ignore();
                            cout << "Enter Room Name: ";
                            cin >> ROOM_NAME;
                            cout << "Call Start Time: ";
                            cin >> ON_CALL_START;
                            cout << "Call End Time: ";
                            cin >> ON_CALL_END;
    
                            result = createOnCall(db, BLOCK_FLOOR, ROOM_NAME, ON_CALL_START, ON_CALL_END);

                                if (result == SQLITE_OK) {
                                    cout << "\nOn Call created successfully!" << endl
                                    int lastInsertedOnCallId = sqlite3_last_insert_rowid(db);
                                    displayOnCall(db, lastInsertedOnCallId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating On Call. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(ooChoice == 2){ //read  
                            OnCallList OnCallList;
                            OnCallList.readOnCall(db);
                            OnCallList.displayreadOnCall();

                        return 0;
                        
                        }else if(ooChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*              Update                *" << endl;
                            cout << "**************************************" << endl;
                            cout << "*         1. Block Floor             *" << endl;
                            cout << "*         2. Room Name               *" << endl;
                            cout << "*         3. On Call Start           *" << endl;
                            cout << "*         4. On Call End             *" << endl;
                            cout << "*         5. Back to Main Menu       *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit block floor
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new block floor: ";
                                cin >> BLOCK_FLOOR;
                                cin.ignore();
                                cout << "Enter On Call ID: ";
                                cin >> ONCALL_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE ON_CALL SET BLOCK_FLOOR = ? WHERE ONCALL_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_int(stmt, 1, BLOCK_FLOOR);
                                sqlite3_bind_int(stmt, 2, ONCALL_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit room name
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new room name: ";
                                cin >> ROOM_NAME;
                                cout << "Enter On Call ID: ";
                                cin >> ONCALL_ID;

                                sqlite3_stmt* stmt1;  
                                string sql1 = "UPDATE ON_CALL SET ROOM_NAME = ? WHERE ONCALL_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, ROOM_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, ONCALL_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit on call start
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new on call start(DD-MM-YYYY HH:MMam/pm): ";
                                cin >> ON_CALL_START;
                                cout << "Enter On Call ID: ";
                                cin >> ONCALL_ID;

                                sqlite3_stmt* stmt2; 
                                string sql2 = "UPDATE ON_CALL SET ON_CALL_START = ? WHERE ONCALL_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt2, 1, ON_CALL_START.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt2, 2, ONCALL_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit on call end
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new on call end(DD-MM-YY HH:MMam/pm): ";
                                cin >> ON_CALL_END;
                                cout << "Enter On Call ID: ";
                                cin >> ONCALL_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE ON_CALL SET ON_CALL_END = ? WHERE ONCALL_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, ON_CALL_END.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, ONCALL_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else if(editChoice == 5){ //back
                                break;
                            }else{ //back
                                break;
                            }
                        
                        }else if(ooChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the on call id to delete: ";
                            cin >> ONCALL_ID;
                            result = deleteOnCall(db, ONCALL_ID);

                            if (result != 0) {
                                cerr << "Failed to delete on call." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(ooChoice == 5){ //back
                            break;
                        }else{                        
                        }
                    }else if (choice == 5) { //Visit Dtails  
                        cout << "*************************************************" << endl;
                        cout << "*                 Visit Details                 *" << endl;
                        cout << "*************************************************" << endl;
                        cout << "*                   1. Create                   *" << endl;
                        cout << "*                   2. Read                     *" << endl;
                        cout << "*                   3. Update                   *" << endl;
                        cout << "*                   4. Delete                   *" << endl;
                        cout << "*                   5. Back                     *" << endl;
                        cout << "*************************************************" << endl;

                        int vdChoice, VISIT_ID, ROOM_ID;
                        cin >> vdChoice;
                        string VISITOR_NAME,VISIT_DURATION,VISIT_DATE,RELATIONSHIP;

                        if (vdChoice == 1){ //create

                            cout << "Enter Room Id: ";
                            cin >> ROOM_ID;
                            cin.ignore();
                            cout << "Enter Visitor Name: ";
                            cin >> VISITOR_NAME;
                            cout << "Enter Visit Duration: ";
                            cin >> VISIT_DURATION;
                            cout << "Visit Date (DD-MM-YYYY): ";
                            cin >> VISIT_DATE;
                            cout << "Enter Relationship with Patient: ";
                            cin >> RELATIONSHIP;

                            result = createVisitDetails(db, ROOM_ID, VISITOR_NAME, VISIT_DURATION, VISIT_DATE, RELATIONSHIP);

                                if (result == SQLITE_OK) {
                                    cout << "\nVisit details created successfully!" << endl;
                                    int lastInsertedVisitDetailsId = sqlite3_last_insert_rowid(db);
                                    displayVisitDetails(db, lastInsertedVisitDetailsId);
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Error creating Visit Details. Please try again." << endl;
                                    return result;
                                }
                          
                        }else if(vdChoice == 2){ //read  
                            VisitDetailsList VisitDetailsList;
                            VisitDetailsList.readVisitDetails(db);
                            VisitDetailsList.displayreadVisitDetails();

                        return 0;
                        
                        }else if(vdChoice == 3){ //update
                            cout << "**************************************" << endl;
                            cout << "*              Update                *" << endl;
                            cout << "**************************************" << endl;
                            cout << "*         1. Room Id                 *" << endl;
                            cout << "*         2. Visitor Name            *" << endl;
                            cout << "*         3. Visit Duration          *" << endl;
                            cout << "*         4. Visit Date              *" << endl;
                            cout << "*         5. Relationship            *" << endl;
                            cout << "*         6. Back to Main Menu       *" << endl;
                            cout << "**************************************" << endl;

                            int editChoice;
                            cin >> editChoice;
                            
                            if (editChoice == 1){ //edit room id
                                    if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new room id: ";
                                cin >> ROOM_ID;
                                cin.ignore();
                                cout << "Enter Visit ID: ";
                                cin >> VISIT_ID;

                                sqlite3_stmt* stmt;
                                string sql = "UPDATE VISIT_DETAILS SET ROOM_ID = ? WHERE VISIT_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_int(stmt, 1, ROOM_ID);
                                sqlite3_bind_int(stmt, 2, VISIT_ID);

                                result = sqlite3_step(stmt);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 2){ //edit visitor name
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new visitor name: ";
                                cin >> VISITOR_NAME;
                                cout << "Enter Visit ID: ";
                                cin >> VISIT_ID;

                                sqlite3_stmt* stmt1;  
                                string sql1 = "UPDATE VISIT_DETAILS SET VISITOR_NAME = ? WHERE VISIT_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt1, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt1, 1, VISITOR_NAME.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt1, 2, VISIT_ID);

                                result = sqlite3_step(stmt1);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt1);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 3){ //edit visit duration
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new visit duration: ";
                                cin >> VISIT_DURATION;
                                cout << "Enter Visit ID: ";
                                cin >> VISIT_ID;

                                sqlite3_stmt* stmt2; 
                                string sql2 = "UPDATE VISIT_DETAILS SET VISIT_DURATION = ? WHERE VISIT_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt2, 1, VISIT_DURATION.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt2, 2, VISIT_ID);

                                result = sqlite3_step(stmt2);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt2);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 4){ //edit visit date
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new visit date: ";
                                cin >> VISIT_DATE;
                                cout << "Enter Visit ID: ";
                                cin >> VISIT_ID;

                                sqlite3_stmt* stmt3;  
                                string sql3 = "UPDATE VISIT_DETAILS SET VISIT_DATE = ? WHERE VISIT_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt3, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt3, 1, VISIT_DATE.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt3, 2, VISIT_ID);

                                result = sqlite3_step(stmt3);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt3);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;
                            }else if(editChoice == 5){ //edit RELATIONSHIP
                                 if (result) {
                                    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                    return (-1);
                                }

                                cout << "Enter new Relationship with Patient: ";
                                cin >> RELATIONSHIP;
                                cout << "Enter visit ID: ";
                                cin >> VISIT_ID;

                                sqlite3_stmt* stmt4;  
                                string sql4 = "UPDATE VISIT_DETAILS SET RELATIONSHIP = ? WHERE VISIT_ID = ?;";

                                result = sqlite3_prepare_v2(db, sql4.c_str(), -1, &stmt4, 0);

                                if (result != SQLITE_OK) {
                                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                sqlite3_bind_text(stmt4, 1, RELATIONSHIP.c_str(), -1, SQLITE_STATIC);
                                sqlite3_bind_int(stmt4, 2, VISIT_ID);

                                result = sqlite3_step(stmt4);

                                if (result != SQLITE_DONE) {
                                    cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
                                    sqlite3_close(db);
                                    return (-1);
                                }

                                // Finalize the statement
                                sqlite3_finalize(stmt4);

                                cout << "Update successful!" << endl;

                                sqlite3_close(db);
                                break;

                            }else if(editChoice == 6){ //BACK 
                                break;
                            }else{ //back
                                break;
                            }
                        
                        }else if(vdChoice == 4){ //delete

                            if (result) {
                                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                                return -1;
                            }

                            cout << "Enter the visit id to delete: ";
                            cin >> VISIT_ID;
                            result = deleteVisitDetails(db, VISIT_ID);

                            if (result != 0) {
                                cerr << "Failed to delete visit details." << endl;
                            }
                            
                            sqlite3_close(db);
                            return 0;
                        }else if(vdChoice == 5){ //back
                            break;
                        }else{                        
                        }
                    }else if (choice == 6){ //Logout
                        cout << "Logging out..." << endl;
                        if (loggout != 6) {
                                    cout << "\nLogout successfully!" << endl;
                                    sqlite3_close(db);
                                    return 0;
                                } else {
                                    cout << "Logout failed. Please try again." << endl;
                                    return loggout;
                                }
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                
                }
            }
                        
            
             //sign up
        }else if (choice == 3) {
            sqlite3 *db;
            int result = sqlite3_open("hospital.db", &db);

            if (result != SQLITE_OK) {
                cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
                return result;
            }
            bool loggedIn = false;
            string USERNAME, PASSWORD, ROLE;
            
            cout << "Enter a new username: ";
            cin >> USERNAME;
            cout << "Enter a new password: ";
            cin >> PASSWORD;
            cout << "Enter the role (doctor/nurse): ";
            cin >> ROLE;

            result = registerUser(db, USERNAME, PASSWORD, ROLE);

            if (result == SQLITE_OK) {
                cout << "Registration successful!" << endl;
            } else {
                cout << "Registration failed. Please try again." << endl;
            }
            break;                        

        } else if(choice == 4){ //Exit
                cout << "Thank you for visiting our website!" << endl;
            break;

        } else{
                cout << "Invalid choice. Please try again." << endl;
            }                    
        
        return 0;   
    }
}
    

    