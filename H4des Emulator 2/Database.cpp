/* 
 * File:   Database.cpp
 * Author: DougM
 * 
 * Created on 9 de Dezembro de 2010, 19:06
 */

#include "Database.h"

Database::Database() {
    host = "localhost";
    username = "root";
    password = "super";
    database = "h4des";
    port = 3306;

    MutexSQL = PTHREAD_MUTEX_INITIALIZER;

    mysql_library_init(0, NULL, NULL);
}

Database::~Database() {
    mysql_library_end();
}

bool Database::init() {
    mysql = mysql_init(0);

    if (!mysql) {
        return false;
    }

    return true;
}

bool Database::connect() {
    if (!mysql_real_connect(mysql, host, username, password, database, port, NULL, 0)) {
        return false;
    }

    return true;
}

void Database::close() {
    mysql_close(mysql);
}

char* Database::getVersion() {
    return mysql_get_server_version(mysql);
}

MYSQL_RES* Database::execute(char* query, ...) {
    va_list ap;
    va_start(ap, query);
    vsprintf(query, query, ap);
    va_end(ap);
    mysql_thread_init();
    int erro = mysql_query(mysql, query);
    if (erro > 0) {
        pthread_mutex_unlock(&MutexSQL);
        return NULL;
    }
    MYSQL_RES* res = mysql_store_result(mysql);
    mysql_free_result(res);
    mysql_thread_end();
    return res;
}

void Database::ping() {
    mysql_ping(mysql);
}

void Database::wait() {
    while (mysql_list_processes(mysql)) {}
}
