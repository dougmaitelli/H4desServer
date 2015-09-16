/*
 * File:   Log.cpp
 * Author: Douglas Maitelli
 *
 * Created on April, 25 2011, 19:57
 */

#include "Log.h"

string Log::getColorCode(Color foreground = NONE, Color background = NONE) {
    char num_s[3];
    string s = "\033[";

    if (!foreground && !background) s += "0";

    if (foreground) {
        sprintf(num_s, "%d", 29 + foreground);
        s += num_s;

        if (background) s += ";";
    }

    if (background) {
        sprintf(num_s, "%d", 39 + background);
        s += num_s;
    }

    return s + "m";
}

void Log::write(MsgType type, char* text, ...) {
    va_list ap;
    va_start(ap, text);
    char* textF;
    vsprintf(textF, text, ap);
    va_end(ap);

    Color color = NONE;

    char* textC;
    switch (type) {
        case LOGO:
            cout << getColorCode(RED);
            cout << "               /-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\" << endl;
            cout << "              /      ___ ___    _____     .___                  \\" << endl;
            cout << "              <     /   |   \\  /  |  |  __| _/____   ______     >" << endl;
            cout << "              <    /    ~    \\/   |  |_/ __ |/ __ \\ /  ___/     >" << endl;
            cout << "              <    \\    Y    /    ^   / /_/ \\  ___/ \\___ \\      >" << endl;
            cout << "              <     \\___|_  /\\____   |\\____ |\\___  >____  >     >" << endl;
            cout << "              <           \\/      |__|     \\/    \\/     \\/      >" << endl;
            cout << "              <               E  M  U  L  A  T  O  R            >" << endl;
            cout << "              \\             U  N  I  T     T  E  A  M           /" << endl;
            cout << "               \\-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-/" << endl;
            break;
        case SHOW_MSG:
            textC = textF;
            break;
        case SQL_ERROR:
            color = MAGENTA;
            sprintf(textC, "[SQL ERROR]: %s", textF);
            break;
        case SERVER_ERROR:
            color = RED;
            sprintf(textC, "[SERVER ERROR]: %s", textF);
            break;
        case WARNING:
            color = YELLOW;
            sprintf(textC, "[WARNING]: %s", textF);
            break;
        case SYSTEM:
            color = GREEN;
            sprintf(textC, "[SYSTEM]: %s", textF);
            break;
        case ADM_ACTION:
            color = BLUE;
            sprintf(textC, "[ADM ACTION]: %s", textF);
            break;
        case GM_ACTION:
            color = YELLOW;
            sprintf(textC, "[GM ACTION]: %s", textF);
            break;
        case LOAD:
            color = CYAN;
            sprintf(textC, "[LOADING]: %s", textF);
            break;
        case HACK:
            color = RED;
            sprintf(textC, "[HACK]: %s", textF);
            break;
        case CLIENT:
            color = CYAN;
            sprintf(textC, "[CLIENT]: %s", textF);
            break;
    }
    printColor(color, textC);

    pthread_mutex_lock(&mutexLOG);

    FILE* file;
    switch (type) {
        case SQL_ERROR:
            file = fopen("logs/Sql_Error-log.txt", "a+");
            break;
        case SERVER_ERROR:
            file = fopen("logs/Server_Error-log.txt", "a+");
            break;
        case WARNING:
            file = fopen("logs/Warning-log.txt", "a+");
            break;
        case ADM_ACTION:
            file = fopen("logs/ADM_Action-log.txt", "a+");
            break;
        case GM_ACTION:
            file = fopen("logs/GM_Action-log.txt", "a+");
            break;
        case HACK:
            file = fopen("logs/Hack-log.txt", "a+");
            break;
        case CLIENT:
            file = fopen("logs/Client-log.txt", "a+");
            break;
        default:
            file = NULL;
            break;
    }

    if (file != NULL) {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        fprintf(file, "[%d/%d/%d %d:%d:%d]", now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
        fprintf(file, textC);
        fputc('\n', file);
        fclose(file);
    }

    pthread_mutex_unlock(&mutexLOG);
}

void Log::printColor(Color color, string text){
    cout << getColorCode(color) << text << endl;
}
