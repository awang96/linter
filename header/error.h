/*
** Filename : error.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/18
**
** Description : Header file for error.c
*/

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "rule_list.h"
#include "file_list.h"


Error* initError(unsigned int line, char* errorName, char* filename);
int addError(Error** el, unsigned int line, char* errorName, char* filename);
int delErrorList(Error** el);
int delError(Error** el);

#endif // ERROR_H
