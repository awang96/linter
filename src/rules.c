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

#ifdef _WIN32
#define LINE_SEP "\n\r"
#else
#define LINE_SEP "\n"
#endif


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
        loopRulesOnLine(rule, line, 0);
    }

    return 0;
}

int getNbIndents(char* line, int nb_indent) {
    char* substr;

    if (!line) return nb_indent;

    printf("a\n");
    while ((substr = strchr(line, '{'))) {
        printf("%s %d\n", substr, strlen(line));
        nb_indent++;
        if (strlen(line) <= 2) break;
        substr += sizeof(char);
    }
    printf("c\n");
    while ((substr = strchr(line, '}'))) {
        nb_indent--;
        substr += sizeof(char);
    }

    return nb_indent;
}


int applyRulesBuffer(RuleList* rule, char* source, Error **errors, char *filename)
{
    if (!rule || !source) {
        return 1;
    }
    int nb_line = 0;
    // strdup to avoid mutating the original source
    char* dup = strdup(source);
    char* line = strtok(dup, LINE_SEP);
    int nb_indent = 1;

    while (line) {
        nb_line += 1;
        //nb_indent = getNbIndents(line, nb_indent);
        printf("%03d | %d | %s\n", nb_line, nb_indent, line);
        loopRulesOnLine(rule, line, nb_indent, filename);
        line = strtok(NULL, LINE_SEP);
    }
    free(dup);

    return 0;
}


void loopRulesOnLine(RuleList* rules, char* line, int nb_indent, char* filename)
{
    RuleList* mut = rules;

    while (mut) {
        //if (!strcmp(mut->name, "line-contains-char") && mut->value) {
        //    if (strstr(line, "char")) {
        //        fprintf(stderr, " ^ this line contains 'char'\n");
        //    }
        //}
        if (!strcmp(mut->name, "operators-spacing") && mut->value) {
            if (!operatorsSpacing(line)) { continue; }
            fprintf(stderr, " ^ operators spacing\n");
        }
        if (!strcmp(mut->name, "array-bracket-eol") && mut->value) {
            if (bracketEOL(line))
                printf(" ^ array-bracket-eol\n");
        }
        if (!strcmp(mut->name, "operators-spacing") && mut->value) {
            //operatorsSpacing(value);
        }
        if (!strcmp(mut->name, "comma-spacing") && mut->value) {
            if (commaSpacing(line))
                printf(" ^ comma-spacing");
        }
        if (!strcmp(mut->name, "indent") && mut->value) {
            //indent(value);
        }
        if (!strcmp(mut->name, "no-multi-declaration") && mut->value) {
            if (noMultiDeclaration(line)) {
                printf(" ^ no-multi-declaration");
            }
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
