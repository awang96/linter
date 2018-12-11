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
    //char* primaryTypes[55] = {"int", "char", "float", "long", "double", "short", "bool"};
    //char* substr1, substr2;

    for (int i = 0; i < 7; i++) {
        /*if ((substr1 = strstr(line, primaryTypes[i]))) {
            if ((substr2 = strchr(line, ','))) {
                return 1;
            }
        }*/
        printf("%s ", primaryTypes[i]);
    }

    return 0;
}
