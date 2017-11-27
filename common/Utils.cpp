/* 
 * File:   Utils.cpp
 * Author: Douglas Maitelli
 * 
 * Created on April, 14 2011, 20:08
 */

#include "Utils.h"

string Utils::addSlashes(string str) {
    string str2;

    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '\\' || str[i] == '"' || str[i] == '\'') {
            str2 += '\\';
        }

        str2 += str[i];
    }

    return str2;
}

string Utils::trimStr(string str) {
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
