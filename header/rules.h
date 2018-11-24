#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "coding_norms.h"


#ifndef RULE_H
#define RULE_H

int applyRules(RuleList* rule, FILE* f);
void loopRulesOnLine(RuleList* mutableru, char* line);
char* removeComment(char* line, int* comment);

#endif // RULE_H
