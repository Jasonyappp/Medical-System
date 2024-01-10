#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
using namespace std;

class Patient {
public:
    int patientID;
    string patientName;

    Patient(int id, string n) : patientID(id), patientName(n) {}
};

Patient* patientLogin();
void displayInvoice(sqlite3* db, int PAYMENT_ID);
void displayAppointment(sqlite3* db, int APPOINT_ID);

#endif 
