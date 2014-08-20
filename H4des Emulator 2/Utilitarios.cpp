/* 
 * File:   Utilitarios.cpp
 * Author: DougM
 * 
 * Created on 14 de Abril de 2011, 20:08
 */

#include "Utilitarios.h"

string Utilitarios::addSlashes(string str) {
    string str2;

    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '\\' || str[i] == '"' || str[i] == '\'') {
            str2 += '\\';
        }

        str2 += str[i];
    }

    return str2;
}

string Utilitarios::trimStr(string str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            str.erase(i);
            i--;
            continue;
        }

        break;
    }

    return str;
}
