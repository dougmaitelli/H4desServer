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

class Log {
private:
    static pthread_mutex_t mutexLOG;

    static string getColorCode(Color, Color);
    static void printColor(Color, string);

public:
    static void writeLogo();
    static void write(MsgType, string, ...);
};

#endif	/* LOG_H */

