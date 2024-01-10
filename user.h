#ifndef USER_H
#define USER_H
#include <iostream>
#include "sqlite3.h"
using namespace std;

int registerUser(sqlite3 *db, const string &USERNAME, const string &PASSWORD, const string &ROLE);
bool authenticateUser(sqlite3 *db, const string &USERNAME, const string &PASSWORD, const string &ROLE);

#endif