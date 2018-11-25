/*
** Filename : rules.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/19
**
** Description : Apply rules
*/

#include <rules.h>

#include "rules.h"
#include "coding_norms.h"


int applyRules(RuleList* rule, FILE* f)
{
    char line[200];
    int nb_line = 0;
    char* lineWoComment;
    int comment = 0;

    if (!rule) {
        return 1;
    }

    while (fgets(line, 200, f)) {
        nb_line += 1;

        if ((lineWoComment = removeComment(line, &comment)) == NULL) {
            printf("%03d |\n", nb_line);
            continue;
        }

        printf("%03d | %s", nb_line, lineWoComment);
        loopRulesOnLine(rule, line);
    }

    return 0;
}


void loopRulesOnLine(RuleList* rules, char* line)
{
    RuleList* mut = rules;
    while (mut) {
        if (!strcmp(mut->name, "line-contains-char") && mut->value) {
            if (strstr(line, "char")) {
                fprintf(stderr, "  ^ this line contains 'char'\n");
            }
        }
        if (!strcmp(mut->name, "operators-spacing") && mut->value) {
            if (!operatorsSpacing(line)) { continue; }
            fprintf(stderr, " ^ operators spacing\n");
        }
        if (!strcmp(mut->name, "array-bracket-eol") && mut->value) {
            // arrayBracketEol(value);
            // printf("ok %s", line);
        }
        if (!strcmp(mut->name, "operators-spacing") && mut->value) {
            //operatorsSpacing(value);
        }
        if (!strcmp(mut->name, "comma-spacing") && mut->value) {
            //commaSpacing(value);
        }
        if (!strcmp(mut->name, "indent") && mut->value) {
            //indent(value);
        }
        mut = mut->next;
    }
}


char* removeComment(char* line, int* comment)
{
    size_t len;
    char* index;
    char* ret;

    if ((index = strstr(line, "//"))) {
        if (index[0] == line[0]) {
            return NULL;
        }
        len = strlen(line) - strlen(index);
        int onlySpaces = 1;
        for (size_t i = 0; i < len; i += 1) {
            if (line[i] != ' ') {
                onlySpaces = 0;
                break;
            }
        }
        if (onlySpaces) {
            return NULL;
        }
        ret = malloc(len * sizeof(char));
        strncpy(ret, line, len);
        ret[len - 1] = '\0';
        return ret;
    }

    if (strstr(line, "/*")) {
        *comment = 1;
        return NULL;
    }

    if (strstr(line, "*/")) {
        *comment = 0;
        return NULL;
    }

    if (*comment) {
        return NULL;
    }

    return line;
}


bool isValidVariableDeclaration(char* s)
{
    return true;
}


bool isValidPrototypeDeclaration(char* s)
{
    return true;
}
