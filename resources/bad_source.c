/**
 * A top comment
 */

// inline comment
unknown_variable /* weird comment */ = 7; // inline comment

/**
 * Comment above function
 * a bit longer
 * @return
 */
unknown_function/* weird comment */() {
    /* weird comment */return;
}

int good_global = /* weird comment */ 0;
int/* problematic comment */problem = 0;

int good_function() {
    return 0;
}

/*
** Filename : coding_norms.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/08
**
** Description : Functions to check the coding norms rules
*/

#include "coding_norms.h"

/*** Check if brackets is at the end of the line ***/
/** Params **/
/* char *line: line to be analyzed */
/** Return **/
/* 1 : Failure
   0 : Success */
int bracketEOL(char* line)
{
    int indexBracketLen;
    char* indexBracket;
    if (!line) {
        return 1;
    }
    indexBracket = strpbrk(line, "{}");
    // Check if there is a bracket in the line
    if (!indexBracket) {
        return 0;
    }
    indexBracketLen = strlen(indexBracket);
    // Check if the bracket is at EOL or before '\n'
    if (indexBracketLen == 1 || indexBracketLen == 2) {
        return 0;
    }
    return 1;
}

/*** Check if there are quotes in the line ***/
/** Params **/
/* char *line: line to be analyzed */
/** Return **/
/* 1 : Failure
   0 : Success
   int *indexQuoteBegin
   int *indexQuoteEnd */
int checkQuote(char* line, int* indexQuoteBegin, int* indexQuoteEnd)
{
    char* quoteBegin;
    char* quoteEnd;
    if (!line) {
        return 1;
    }
    if ((quoteBegin = strchr(line, '"'))) {
        if ((quoteEnd = strchr(quoteBegin, '"'))) {
            *indexQuoteBegin = strlen(line) - strlen(quoteBegin);
            *indexQuoteEnd = strlen(line) - strlen(quoteEnd);
            return 0;
        }
    } else if ((quoteBegin = strchr(line, '\''))) {
        if ((quoteEnd = strchr(line, '\''))) {
            *indexQuoteBegin = strlen(line) - strlen(quoteBegin);
            *indexQuoteEnd = strlen(line) - strlen(quoteEnd);
            return 0;
        }
    }
    return 1;
}

/*** Check if there are spaces before and after a binary operator ***/
/** Params **/
/* char *line : line to be analyzed */
/** Return **/
/* 1 : Failure
   0 : Success */
int operatorsSpacing(char* line)
{
    char* operatorIndex;
    char* operators = "+-%=!&|<>^~";
    if (!line) {
        return 1;
    }
    // Parsing the line
    operatorIndex = line;
    while ((operatorIndex = strpbrk(operatorIndex, operators))) {
        // Check ++ and --
        if (*operatorIndex == '+' || *operatorIndex == '-') {
            if (*(operatorIndex + 1) == *operatorIndex) {
                operatorIndex += 2 * sizeof(char);
                continue;
            }
        }
        // Check if there is a space before
        if (line[strlen(line) - strlen(operatorIndex) - 1] != ' ') {
            return 1;
        }
        // Check space after
        if (*(operatorIndex + 1) == ' ' && *operatorIndex != '!') {
            operatorIndex += sizeof(char);
            continue;
        }
        // If an '=' is after the operator, check the space after
        if (*(operatorIndex + 1) == '=' && *(operatorIndex + 2) == ' ') {
            operatorIndex += 2 * sizeof(char);
            continue;
        }
        // Check case <<, >>, &&, ||
        if (*operatorIndex == '<' || *operatorIndex == '>' || *operatorIndex == '&' || *operatorIndex == '|') {
            if (*(operatorIndex + 1) == *operatorIndex &&
                *(operatorIndex + 2) == ' ') {
                operatorIndex += 3 * sizeof(char);
                continue;
            }
        }
        //check case >>= and <<=
        if ((*operatorIndex == '<' || *operatorIndex == '>') &&
            *(operatorIndex + 1) == *operatorIndex &&
            *(operatorIndex + 2) == '=' &&
            *(operatorIndex + 3) == ' ') {
            operatorIndex += 4 * sizeof(char);
            continue;
        }
        if (*operatorIndex == '!') {
            operatorIndex += sizeof(char);
            continue;
        }
        return 1;
    }
    return 0;
}

/*** Check if there's a space after a comma ***/
/** Params **/
/* char *line : line to be analyzed */
/** Return **/
/* 1 : Failure
   0 : Success */
int commaSpacing(char* line)
{
    char* indexComma;
    if (!line) {
        return 1;
    }
    indexComma = line;
    while ((indexComma = strchr(indexComma, ','))) {
        if (*(indexComma + 1) != ' ') {
            return 1;
        }
        indexComma += sizeof(char);
    }
    return 0;
}

/*** Check if the indentation is correct ***/
/** Params **/
/* char *line : line to be analyzed
   int n : number of spaces for indent
   int i : number of indent */
/** Return **/
/* 1 : Failure
   0 : Success */
int indent(char* line, int n, int i)
{
    int countI;
    int countN;
    int countLine = 0;
    if (!line || n <= 0 || i <= 0) {
        return 1;
    }
    for (countI = 0; countI < i; countI++) {
        for (countN = 0; countN < n; countN++) {
            if (line[countLine] != ' ') {
                return 1;
            }
            countLine++;
        }
    }
    if (line[countLine] == ' ') {
        return 1;
    }
    return 0;
}

/*** Check comment header ***/
/** Params **/
/* FILE *f : handle to the file to parse in reading mode */
/** Return **/
/* 1 : Failure
   0 : Success */
int commentsHeader(FILE* f)
{
    char line[MAX_LINE];
    if (!f) {
        return 1;
    }
    if (fseek(f, 0, SEEK_SET)) {
        return 1;
    }
    if (!fgets(line, MAX_LINE, f)) {
        return 1;
    }
    if (line[0] != '/' || line[1] != '*') {
        return 1;
    }
    return 1;
}

/*** Check the number of characters in a line ***/
/** Params **/
/* char *line : line to be analyzed
   int n : max number of characters in a line */
/** Return **/
/* 1 : Failure
   0 : Success */
int maxLineNumbers(char* line, int n)
{
    if (!line || n <= 0) {
        return 1;
    }
    if (strlen(line) > n) {
        return 1;
    }
    return 0;
}

/*** Check the number of lines in a file ***/
/** Params **/
/* int lines : number of lines in the file
   int n : max number of lines in a file */
/** Return **/
/* 1 : Failure
   0 : Success */
int maxFileLineNumbers(int lines, int n)
{
    if (lines <= 0 || n <= 0) {
        return 1;
    }
    if (lines > n) {
        return 1;
    }
    return 0;
}

/*** Check trailing spaces ***/
/** Params **/
/* char *line : line to be analyzed */
/** Return **/
/* 1 : Failure
   0 : Success */
int noTrailingSpaces(char* line)
{
    if (!line) {
        return 1;
    }
    if (line[strlen(line) - 2] == ' ') {
        return 1;
    }
    return 0;
}
