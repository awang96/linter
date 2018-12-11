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


int getNbIndents(char* line, int nb_indent) {
    char* substr;

    if (!line) return nb_indent;

    if(strchr(line,'{'))
	nb_indent++;
    if(strchr(line, '}'))
	nb_indent--;

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
    RuleList *mut = rule;
    while (line) {
        nb_line += 1;
        //nb_indent = getNbIndents(line, nb_indent);
        printf("%03d | %d | %s\n", nb_line, nb_indent, line);
        loopRulesOnLine(rule, line, nb_indent, filename);
        line = strtok(NULL, LINE_SEP);
    }
    while(mut){
	if(!strcmp(mut->name, "max-file-line-numbers") && mut->value){
	    if(maxFileLineNumbers(nb_line, mut->value))
		fprintf(stderr, " ^ max-file-line-numbers");
	}
	mut = mut->next;
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
        if (!strcmp(mut->name, "array-bracket-eol") && mut->value) {
            if (bracketEOL(line))
                fprintf(stderr, " ^ array-bracket-eol\n");
        }
        if (!strcmp(mut->name, "operators-spacing") && mut->value) {
            if(operatorsSpacing(line))
		fprintf(stderr, " ^ operators-spacing\n");
        }
        if (!strcmp(mut->name, "comma-spacing") && mut->value) {
            if (commaSpacing(line))
                fprintf(stderr, " ^ comma-spacing\n");
        }
        if (!strcmp(mut->name, "indent") && mut->value) {
	    if(indent(line, mut->value, nb_indent))
		fprintf(stderr, " ^ indent\n");
            //indent(value);
        }
        if (!strcmp(mut->name, "no-multi-declaration") && mut->value) {
            if (noMultiDeclaration(line)) {
                fprintf(stderr, " ^ no-multi-declaration\n");
            }
        }
	if(!strcmp(mut->name, "max-line-numbers") && mut->value){
	    if(maxLineNumbers(line, mut->value))
		fprintf(stderr, " ^ max-line-numbers\n");
	}
	if(!strcmp(mut->name, "no-trailing-spaces") && mut->value){
	    if(noTrailingSpaces(line))
		fprintf(stderr, " ^ no-trailing-spaces\n");
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
