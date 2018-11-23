/*
** Filename : config.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/17 by Alexandre WANG
**
** Description : Header file for config.c
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "rule_list.h"
#include "file_list.h"


Config* initConfig(FileList* extends, RuleList* rules, FileList* excluded, char* rec);
int delConfig(Config** config);

#endif // CONFIG_H
