/*
** Filename : lconf.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/18 by Alexandre WANG
**
** Description : Header for lconf.c
*/
#ifndef FILE_H
#define FILE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "file_list.h"
#include "rule_list.h"
#include "config.h"


#define KEY 4
#define KEY_LEN 255
#define LINE 2555

FILE* openLconf(char* path);
Config* getKey(FILE*);
int fillConf(char* line, char* key, Config* conf, unsigned char parent);
int checkKey(char* key);
void getParentLconf(Config* conf);
int parseParent(char* filename, Config* conf);

#endif // FILE_H
