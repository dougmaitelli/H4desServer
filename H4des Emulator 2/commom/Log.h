/*
 * File:   Log.h
 * Author: Douglas Maitelli
 *
 * Created on April, 25 2011, 19:57
 */

#ifndef LOG_H
#define	LOG_H

#include <pthread.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>

using namespace std;

enum MsgType {
    LOGO,
    SHOW_MSG,
    SQL_ERROR,
    SERVER_ERROR,
    WARNING,
    SYSTEM,
    ADM_ACTION,
    GM_ACTION,
    LOAD,
    HACK,
    CLIENT
};

enum Color {
    NONE = 0,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

pthread_mutex_t mutexLOG = PTHREAD_MUTEX_INITIALIZER;

class Log {
public:
    static void write(MsgType, char* = "", ...);

private:
    static string getColorCode(Color, Color);
    static void printColor(Color, string);

};

#endif	/* LOG_H */

