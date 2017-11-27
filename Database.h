/*
 * File:   Database.h
 * Author: Douglas Maitelli
 *
 * Created on December, 9 2010, 19:06
 */

#ifndef DATABASE_H
#define	DATABASE_H

//#include "mysql_driver.h"

//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>

class Database {
private:
    char* host;
    char* username;
    char* password;
    char* database;

    //sql::Driver* driver;
    //sql::Connection* con;

public:
    Database();
    virtual ~Database();

    // General
    bool connect();
    void close();
    char* getVersion();
    void wait();
    //const sql::Connection* getConnection() const;
};

#endif	/* DATABASE_H */
