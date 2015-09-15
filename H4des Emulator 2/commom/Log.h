/*
 * File:   Log.h
 * Author: Douglas Maitelli
 *
 * Created on April, 25 2011, 19:57
 */

#ifndef LOG_H
#define	LOG_H

#include <pthread.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdarg.h>

using namespace std;

pthread_mutex_t mutexLOG = PTHREAD_MUTEX_INITIALIZER;

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

enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_TURQUEY,
    DARK_RED,
    DARK_PURPLE,
    BROWN,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    TURQUEY,
    RED,
    PURPLE,
    YELLOW,
    WHITE
};

static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

class Log {
public:
    static void foregroundColor(int);
    static void backgroundColor(int);
    static void write(MsgType, char* = "", ...);

private:

};

#endif	/* LOG_H */

