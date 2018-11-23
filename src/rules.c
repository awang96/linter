/*
** Filename : rules.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/19
**
** Description : Apply rules
*/

#include "rules.h"
#include "coding_norms.h"


int applyRules(RuleList* r, FILE* f)
{
    char line[200];
    int nb_line = 0;
    char* lineWoComment;
    int comment = 0;

    if (!r) {
        return 1;
    }
    RuleList* p;
    while (fgets(line, 200, f)) {
        p = r;
        nb_line += 1;

        if ((lineWoComment = removeComment(line, &comment)) == NULL) {
            printf("%03d |\n", nb_line);
            continue;
        }

        printf("%03d | %s", nb_line, lineWoComment);
        loopRulesOnLine(p, line);
    }

    return 0;
}


void loopRulesOnLine(RuleList* rule, char* line)
{
    while (rule) {
        if (!strcmp(rule->name, "operators-spacing") && rule->value) {
            if (!operatorsSpacing(line)) { continue; }
            fprintf(stderr, " ^ operators spacing\n");
        }
        if (!strcmp(rule->name, "array-bracket-eol") && rule->value) {
            // arrayBracketEol(value);
            // printf("ok %s", line);
        }
        if (!strcmp(rule->name, "operators-spacing") && rule->value) {
            //operatorsSpacing(value);
        }
        if (!strcmp(rule->name, "comma-spacing") && rule->value) {
            //commaSpacing(value);
        }
        if (!strcmp(rule->name, "indent") && rule->value) {
            //indent(value);
        }
        rule = rule->next;
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
