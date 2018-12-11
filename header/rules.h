#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "coding_norms.h"
#include "coding_rules.h"
#include "error.h"

#ifndef RULE_H
#define RULE_H

int getNbIndents(char* line, int nb_indent);
int applyRules(RuleList* rule, FILE* f);
int applyRulesBuffer(RuleList* rule, char* source, Error **errors, char* filename);
void loopRulesOnLine(RuleList* rules, char* line, int nb_indent, char *filename);
char* removeComment(char* line, int* comment);
bool isValidVariableDeclaration(char*);
bool isValidPrototypeDeclaration(char*);

#endif // RULE_H
