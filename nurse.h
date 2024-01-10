#ifndef NURSER_H
#define NURSER_H
#include <iostream>
#include "sqlite3.h"
using namespace std;

class Nurse {
public:
    int nurseID;
    string nurseName;
    string role;

    Nurse(int id, string name, string r) : nurseID(id), nurseName(name), role(r) {}
};
Nurse* nurseLogin();
static int callback(void* data, int argc, char** argv, char** azColName);


int createDrugsDetails(sqlite3 *db, const string &DRUGS_NAME, int DRUGS_QUANTITY, const string &DRUGS_PDATE, const string &DRUGS_EXPDATE);
struct DrugsDetails {
    int DRUGS_ID,DRUGS_QUANTITY;
    string DRUGS_NAME,DRUGS_PDATE,DRUGS_EXPDATE;

    DrugsDetails* next; 
};
class DrugsDetailsList {
private:
    DrugsDetails* head; 

public:
    DrugsDetailsList() : head(nullptr) {}

    void insertDrugsDetails(int DRUGS_ID, int DRUGS_QUANTITY, const string& DRUGS_NAME, const string& DRUGS_PDATE, const string& DRUGS_EXPDATE) {
    DrugsDetails* newRecord = new DrugsDetails{DRUGS_ID, DRUGS_QUANTITY, DRUGS_NAME, DRUGS_PDATE, DRUGS_EXPDATE, nullptr};

    if (head == nullptr) {
        head = newRecord;
    } else {
        newRecord->next = head;
        head = newRecord;
    }
}
        
        void readDrugsDetails(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM DRUGS_DETAILS;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertDrugsDetails(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadDrugsDetails() {
        DrugsDetails* current = head;

        while (current != nullptr) {
            cout << "\nDrugs Id: " << current->DRUGS_ID
                 << "\nDrugs Name: " << current->DRUGS_NAME
                 << "\nDrugs Quantity: " << current->DRUGS_QUANTITY
                 << "\nPurchase Date: " << current->DRUGS_PDATE
                 << "\nExpiry Date: " << current->DRUGS_EXPDATE << endl;

            current = current->next;
        }
    }
};
int deleteDrugsDetails(sqlite3* db, int DRUGS_ID);
void displayDrugsDetails(sqlite3* db, int DRUGS_ID);


int createEquipmentDetails(sqlite3 *db, const string &ITEM_NAME, const string &ITEM_CATERGORY, int ITEM_QUANTITY, const string &ITEM_PDATE, const string &ITEM_COST);
struct EquipmentDetails {
    int EQUIPDETAILS_ID,ITEM_QUANTITY;
    string ITEM_NAME,ITEM_CATERGORY,ITEM_PDATE,ITEM_COST;

    EquipmentDetails* next; 
};
class EquipDetailsList {
private:
    EquipmentDetails* head; 

public:
    EquipDetailsList() : head(nullptr) {}

    void insertEquipDetails(int EQUIPDETAILS_ID, int ITEM_QUANTITY, const string &ITEM_NAME, const string &ITEM_CATERGORY, const string &ITEM_PDATE, const string &ITEM_COST) {
        EquipmentDetails* newRecord = new EquipmentDetails{EQUIPDETAILS_ID, ITEM_QUANTITY, ITEM_NAME,ITEM_CATERGORY,ITEM_PDATE,ITEM_COST, nullptr};

        if (head == nullptr) {
            head = newRecord;
        } else {
            newRecord->next = head;
            head = newRecord;
        }
    }
        
        void readEquipDetails(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM EQUIPMENT_DETAILS;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertEquipDetails(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadEquipDetails() {
        EquipmentDetails* current = head;

        while (current != nullptr) {
            cout << "\nEquipment Id: " << current->EQUIPDETAILS_ID
                 << "\nEquipment Name: " << current->ITEM_NAME
                 << "\nEquipment Catergory: " << current->ITEM_CATERGORY
                 << "\nEquipmeny Quantity: " << current->ITEM_QUANTITY
                 << "\nPurchase Date: " << current->ITEM_PDATE
                 << "\nEquipment Cost: "<< current ->ITEM_COST << endl;

            current = current->next;
        }
    }
};
int deleteEquipmentDetails(sqlite3* db, int EQUIPDETAILS_ID);
void displayEquipmentDetails(sqlite3* db, int EQUIPDETAILS_ID);


int createInventoryDetails(sqlite3 *db, int I_QUANTITY, const string &I_NAME, const string &I_CATERGORY, const string &I_PDATE, const string &I_EXPDATE);
struct InventoryDetails {
    int INTDETAILS_ID, I_QUANTITY;
    string I_NAME, I_CATERGORY, I_PDATE, I_EXPDATE;

    InventoryDetails* next; 
};
class InventoryDetailsList {
private:
    InventoryDetails* head; 

public:
    InventoryDetailsList() : head(nullptr) {}

    void insertInventoryDetails(int INTDETAILS_ID, int I_QUANTITY, const string &I_NAME, const string &I_CATERGORY, const string &I_PDATE, const string &I_EXPDATE) {
        InventoryDetails* newRecord = new InventoryDetails{INTDETAILS_ID, I_QUANTITY, I_NAME, I_CATERGORY, I_PDATE, I_EXPDATE, nullptr};

        if (head == nullptr) {
            head = newRecord;
        } else {
            newRecord->next = head;
            head = newRecord;
        }
    }
        
        void readInventoryDetails(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM INVENTORY_DETAILS;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertInventoryDetails(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadInventoryDetails() {
        InventoryDetails* current = head;

        while (current != nullptr) {
            cout << "\nInventory Id: " << current->INTDETAILS_ID
                 << "\nItem Name: " << current->I_NAME
                 << "\nItem Catergory: " << current->I_CATERGORY
                 << "\nItem Quantity: " << current->I_QUANTITY
                 << "\nPurchase Date: " << current->I_PDATE
                 << "\nExpired Date: "<< current ->I_EXPDATE << endl;

            current = current->next;
        }
    }
};
int deleteInventoryDetails(sqlite3* db, int INTDETAILS_ID);
void displayInventoryDetails(sqlite3* db, int INTDETAILS_ID);


int createOnCall(sqlite3 *db, int BLOCK_FLOOR, const string &ROOM_NAME, const string &ON_CALL_START, const string &ON_CALL_END);
struct OnCall {
    int ONCALL_ID, BLOCK_FLOOR;
    string ROOM_NAME, ON_CALL_START, ON_CALL_END;

    OnCall* next; 
};
class OnCallList {
private:
    OnCall* head; 

public:
    OnCallList() : head(nullptr) {}

    void insertOnCall(int ONCALL_ID, int BLOCK_FLOOR, const string &ROOM_NAME, const string &ON_CALL_START, const string &ON_CALL_END) {
        OnCall* newRecord = new OnCall{ONCALL_ID,BLOCK_FLOOR, ROOM_NAME, ON_CALL_START, ON_CALL_END, nullptr};

        if (head == nullptr) {
            head = newRecord;
        } else {
            newRecord->next = head;
            head = newRecord;
        }
    }
        
        void readOnCall(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM ON_CALL;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertOnCall(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadOnCall() {
        OnCall* current = head;

        while (current != nullptr) {
            cout << "\nOn Call Id: " << current->ONCALL_ID
                 << "\nBlock Floor: " << current->BLOCK_FLOOR
                 << "\nRomm Name: " << current->ROOM_NAME
                 << "\nOn Call Start: " << current->ON_CALL_START
                 << "\nOn Call End: " << current->ON_CALL_END << endl;

            current = current->next;
        }
    }
};
int deleteOnCall(sqlite3* db, int ONCALL_ID);
void displayOnCall(sqlite3* db, int ONCALL_ID);


int createVisitDetails(sqlite3 *db, int ROOM_ID, const string &VISITOR_NAME, const string &VISIT_DURATION, const string &VISIT_DATE, const string &RELATIONSHIP);
struct VisitDetails {
    int VISIT_ID,ROOM_ID;
    string VISITOR_NAME,VISIT_DURATION,VISIT_DATE,RELATIONSHIP;

    VisitDetails* next; 
};
class VisitDetailsList {
private:
    VisitDetails* head; 

public:
    VisitDetailsList() : head(nullptr) {}

    void insertVisitDetails(int VISIT_ID, int ROOM_ID, const string &VISITOR_NAME, const string &VISIT_DURATION, const string &VISIT_DATE, const string &RELATIONSHIP) {
        VisitDetails* newRecord = new VisitDetails{VISIT_ID,ROOM_ID,VISITOR_NAME,VISIT_DURATION,VISIT_DATE,RELATIONSHIP, nullptr};

        if (head == nullptr) {
            head = newRecord;
        } else {
            newRecord->next = head;
            head = newRecord;
        }
    }
        
        void readVisitDetails(sqlite3* db) {
        sqlite3_stmt* stmt;
        string query = "SELECT * FROM VISIT_DETAILS;";

        int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            cerr << "Error preparing query: " << sqlite3_errmsg(db) << endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            insertVisitDetails(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
            );
        }

        sqlite3_finalize(stmt);
    }

    void displayreadVisitDetails() {
        VisitDetails* current = head;

        while (current != nullptr) {
            cout << "\nVisit ID: " << current->VISIT_ID
                 << "\nRoom ID: " << current->ROOM_ID
                 << "\nVisitor Name: " << current->VISITOR_NAME
                 << "\nVisit Duration: " << current->VISIT_DURATION
                 << "\nVisit Date: " << current->VISIT_DATE
                 << "\nRelationship with Patient: " << current ->RELATIONSHIP << endl;

            current = current->next;
        }
    }
};
int deleteVisitDetails(sqlite3* db, int VISIT_ID);
void displayVisitDetails(sqlite3* db, int VISIT_ID);




#endif
