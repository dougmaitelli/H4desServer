/* 
 * File:   Log.cpp
 * Author: DougM
 * 
 * Created on 25 de Abril de 2011, 19:57
 */

#include "Log.h"

void Log::foregroundColor(int color) {
    __FOREGROUND = color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}

void Log::backgroundColor(int color) {
    __BACKGROUND = color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));
}

void Log::write(MsgType type, char* text, ...) {
    pthread_mutex_lock(&mutexLOG);
    va_list ap;
    va_start(ap, text);
    char* textF;
    vsprintf(textF, text, ap);
    va_end(ap);

    char* textC;
    switch (type) {
        case LOGO:
            foregroundColor(RED);
            printf("               /-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\ \n");
            printf("              /      ___ ___    _____     .___                  \\ \n");
            printf("              <     /   |   \\  /  |  |  __| _/____   ______     > \n");
            printf("              <    /    ~    \\/   |  |_/ __ |/ __ \\ /  ___/     > \n");
            printf("              <    \\    Y    /    ^   / /_/ \\  ___/ \\___ \\      > \n");
            printf("              <     \\___|_  /\\____   |\\____ |\\___  >____  >     > \n");
            printf("              <           \\/      |__|     \\/    \\/     \\/      > \n");
            printf("              <               E  M  U  L  A  T  O  R            > \n");
            printf("              \\             U  N  I  T     T  E  A  M           / \n");
            printf("               \\-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-/ \n\n");
            break;
        case SHOW_MSG:
            foregroundColor(GRAY);
            textC = textF;
            break;
        case SQL_ERROR:
            foregroundColor(PURPLE);
            sprintf(textC, "[SQL ERROR]: %s", textF);
            break;
        case SERVER_ERROR:
            foregroundColor(RED);
            sprintf(textC, "[SERVER ERROR]: %s", textF);
            break;
        case WARNING:
            foregroundColor(YELLOW);
            sprintf(textC, "[WARNING]: %s", textF);
            break;
        case SYSTEM:
            foregroundColor(GREEN);
            sprintf(textC, "[SYSTEM]: %s", textF);
            break;
        case ADM_ACTION:
            foregroundColor(BLUE);
            sprintf(textC, "[ADM ACTION]: %s", textF);
            break;
        case GM_ACTION:
            foregroundColor(YELLOW);
            sprintf(textC, "[GM ACTION]: %s", textF);
            break;
        case LOAD:
            foregroundColor(TURQUEY);
            sprintf(textC, "[LOADING]: %s", textF);
            break;
        case HACK:
            foregroundColor(RED);
            sprintf(textC, "[HACK]: %s", textF);
            break;
        case CLIENT:
            foregroundColor(TURQUEY);
            sprintf(textC, "[CLIENT]: %s", textF);
            break;
    }
    cout << textC << endl;
    foregroundColor(WHITE);

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
        SYSTEMTIME st;
        GetSystemTime(&st);
        fprintf(file, "[%d/%d/%d %d:%d:%d]", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
        fprintf(file, textC);
        fputc('\n', file);
        fclose(file);
    }

    pthread_mutex_unlock(&mutexLOG);
}