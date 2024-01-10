#include <iostream>
#include "sqlite3.h"
#include <string>
  
using namespace std;
  
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}
  
int main(int argc, char** argv)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("hospital.db", &DB);
    string query = "SELECT * FROM MEDICAL_RECORD;";
  
    cout << "STATE OF TABLE BEFORE DELETE" << endl;
  
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
  
    string sql = "DROP TABLE MEDICAL_RECORD" ;
  
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Delete Successfully!" << std::endl;
  
    cout << "STATE OF TABLE AFTER DELETE" << endl;
  
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

  
    sqlite3_close(DB);
    return (0);
}