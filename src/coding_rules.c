/*
** Filename : coding_rules.c
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/18 by Alexandre WANG
**
** Description : Functions to check coding rules in a C program
*/

#include "coding_rules.h"

int noMultiDeclaration(char* line) {
    char* primaryTypes[] = {"int", "char", "float", "long", "double", "short", "bool"};

    for (int i = 0; i < 7; i++) {
        if (strstr(line, primaryTypes[i]) && !strchr(line, '(') && !strchr(line, ')')) {
            if (strchr(line, ',')) {
                return 1;
            }
        }
    }

    return 0;
}
