
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "strings.h"


char* appendOneChar(char* str, char c);


char* removeComments(char* prgm)
{
    size_t n = strlen(prgm);
    char* res = calloc(n, sizeof(char));

    // Flags to indicate that single line and multiple line comments
    // have started or not.
    bool s_cmt = false;
    bool m_cmt = false;

    // Traverse the given program
    for (int i = 0; i < n; i++) {
        // If single line comment flag is on, then check for end of it
        if (s_cmt == true && prgm[i] == '\n') {
            s_cmt = false;
            // If multiple line comment is on, then check for end of it
        } else if (m_cmt == true && prgm[i] == '*' && prgm[i + 1] == '/') {
            m_cmt = false;
            i += 1;
            // If this character is in a comment, ignore it
        } else if (s_cmt || m_cmt) {
            continue;
            // Check for beginning of comments and set the appropriate flags
        } else if (prgm[i] == '/' && prgm[i + 1] == '/') {
            s_cmt = true;
            i += 1;
        } else if (prgm[i] == '/' && prgm[i + 1] == '*') {
            m_cmt = true;
            i += 1;
            // If current character is a non-comment character, append it to res
        } else {
            res = appendOneChar(res, prgm[i]);
        }
    }

    return res;
}


char* appendOneChar(char* str, char c)
{
    size_t len = strlen(str);
    char* result = calloc(len + 2, sizeof(char));
    strcpy(result, str);
    result[len] = c;
    free(str);
    return result;
}


char isWhitespace(char c)
{
    return c == ' ' ||
        c == '\n' ||
        c == '\r' ||
        c == '\t' ||
        c == '\v' ||
        c == '\f';
}


char isAlphanumeric(char c)
{
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_';
}
