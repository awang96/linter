/*
** Filename : rules.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/19
**
** Description : Apply rules
*/

#include "../header/rules.h"

int applyRules(RuleList *r, FILE *f) {

    RuleList* p;
    char name[200];
    int value;
    char line[200];
    int nb_line = 0;
    char* lineWoComment;
    int comment = 0;

    if (!r)
        return 1;
    while(fgets(line, 200, f)) {
        p = r;
        nb_line++;
        if ((lineWoComment = removeComment(line, &comment)) != NULL) {

            printf("%s", lineWoComment);
            while(p) {
                strcpy(name, p->name);
                value = p->value;

                if(!strcmp(name, "operators-spacing") && value) {
                    //printf("operators spacing line %d : %d\n", nb_line, operatorsSpacing(line));
                }
                if ( !strcmp(name, "array-bracket-eol") && value) {
                    //arrayBracketEol(value);
                    //printf("ok %s", line);
                }
                if (!strcmp(name, "operators-spacing") && value) {
                   //operatorsSpacing(value);
                }
                if (!strcmp(name, "comma-spacing") && value) {
                    //commaSpacing(value);
                }
                if (!strcmp(name, "indent") && value) {
                    //indent(value);
                }
                p = p->next;
            }
            free(lineWoComment);
        }
    }

    return 0;
}

char* removeComment(char *line, int* comment) {
    int len;
    char* index;
    char* ret;

    if ((index = strstr(line, "//"))) {
        if (index[0] == line[0]) {
            return NULL;
        } else {
            len = strlen(line) - strlen(index);
            ret = malloc(len * sizeof(char));
            strncpy(ret, line, len);
            ret[len - 1] = '\0';
            return ret;
        }
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
