#include <iostream>
#include "sqlite3.h"
#include <string>

int main(int argc, char** argv) {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("hospital.db", &DB);

    std::string sql = "INSERT INTO LAB_RECORD(PATIENT_NAME, BLOOD_PRESSURE, HEART_RATE, BLOOD_SUGAR, XRAY, LR_DATE)"
                       "VALUES('LIM', 'LIM', 'PAY', 'CASH', '32.2', '1-12-2024 11:12pm');";

    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return (-1);
    } else {
        std::cout << "Record created Successfully" << std::endl;
        sqlite3_close(DB);
        return (0);
    }
}
