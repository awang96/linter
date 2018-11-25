#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "coding_norms.h"


#ifndef RULE_H
#define RULE_H

int applyRules(RuleList* rule, FILE* f);
void loopRulesOnLine(RuleList* rules, char* line);
char* removeComment(char* line, int* comment);
bool isValidVariableDeclaration(char*);
bool isValidPrototypeDeclaration(char*);

#endif // RULE_H
