/*
 * File:   Log.h
 * Author: Douglas Maitelli
 *
 * Created on April, 25 2011, 19:57
 */

#ifndef LOG_H
#define	LOG_H

#include <mutex>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

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

#ifdef _WIN32
enum Color {
    NONE = 0,
    BLACK,
    RED = 12,
    GREEN = 10,
    YELLOW = 14,
    BLUE = 9,
    MAGENTA = 13,
    CYAN = 11,
    WHITE = 15
};
#else
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
#endif

class Log {
private:
    static void setColor(Color, Color);
    static void printColor(Color, string);

public:
    static void writeLogo();
    static void write(MsgType, string, ...);
	static void writePercentage(unsigned int, string);
};

#endif	/* LOG_H */

