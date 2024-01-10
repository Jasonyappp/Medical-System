#include <iostream> 
#include "sqlite3.h"
#include <string>

int main(int argc, char** argv) {    
    sqlite3* DB;   
    int exit = 0;

    std::string sql = "CREATE TABLE USERS("
                      "USERS_ID                  INTEGER    PRIMARY KEY  AUTOINCREMENT,"
                      "USERNAME                   TEXT                   NOT NULL,"                      
                      "PASSWORD                   TEXT                   NOT NULL,"                      
                      "ROLE                       TEXT                   NOT NULL); ";                         

    exit = sqlite3_open("hospital.db", &DB);    
    char* messaggeError;    
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);      
    
    if (exit != SQLITE_OK) {        
        std::cerr << "Error Create Table" << std::endl;        
return (-1);    
}  else   {     
        std::cout << "Table created Successfully" << std::endl;    
        sqlite3_close(DB);    
        return (0);   
        }
}