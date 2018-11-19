/*
** Filename : coding_norms.h
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/08
**
** Description : Header file for coding_norms.c
*/

#ifndef CODING_NORMS
#define CODING_NORMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

int bracketEOL(char *line);
int checkQuote(char *line, int *indexQuoteBegin, int *indexQuoteEnd);
int operatorsSpacing(char *line);
int commaSpacing(char *line);
int indent(char *line, int n, int i);
int commentsHeader(FILE *f);
int maxLineNumbers(char *line, int n);
int maxFileLineNumbers(int lines, int n);
int noTrailingSpaces(char *line);

#endif // CODING_NORMSD:\cours2018-2019\S1\C\projet\linter\sources\src\coding_norms.c
