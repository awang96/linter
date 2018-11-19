/*
** Filename : rule_list.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/18 by Alexandre WANG
**
** Description : Header for rule_list.c
*/

#ifndef RULE_LIST_H
#define RULE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

RuleList* initRuleList(char *name, char *value);
unsigned int assignValue(char *value);
int addRule(RuleList **rl, char *line);
int addRuleParent(RuleList **rl, char *line);
int delRule(RuleList **rl);
int delRuleList(RuleList **rl);
void showRuleList(RuleList *rl);
int setNameValue(char *line, char *name, char *value);

#endif // RULE_LIST_H
