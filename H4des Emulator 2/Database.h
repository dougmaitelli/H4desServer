/* 
 * File:   Database.h
 * Author: DougM
 *
 * Created on 9 de Dezembro de 2010, 19:06
 */

#ifndef DATABASE_H
#define	DATABASE_H

#include "include/pthread/pthread.h"
#include "include/mysql/mysql.h"

class Database {
public:
    Database();
    virtual ~Database();
    bool init();
    bool connect();
    void close();
    char* getVersion();
    MYSQL_RES* execute(char*, ...);
    void ping();
    void wait();

private:
    char* host;
    char* username;
    char* password;
    char* database;
    u_short port;

    pthread_mutex_t MutexSQL;

    MYSQL* mysql;
};

#endif	/* DATABASE_H */

