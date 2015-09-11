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

    driver = get_driver_instance();
}

Database::~Database() {
}

bool Database::connect() {
	con = driver->connect(host, username, password);
	con->setSchema(database);

    return true;
}

void Database::close() {
    con->close();
}

char* Database::getVersion() {
    return con->getClientInfo().c_str();
}

void Database::wait() {
}

const sql::Connection* Database::getConnection() const {
	return con;
}

