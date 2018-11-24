
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "strings.h"


void appendToChars(char* res, char* i);


char* removeComments(char* prgm)
{
    size_t n = strlen(prgm);
    char* res = calloc(n, sizeof(char));

    // Flags to indicate that single line and multpile line comments
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
            // Check for beginning of comments and set the approproate flags
        } else if (prgm[i] == '/' && prgm[i + 1] == '/') {
            s_cmt = true;
            i += 1;
        } else if (prgm[i] == '/' && prgm[i + 1] == '*') {
            m_cmt = true;
            i += 1;
            // If current character is a non-comment character, append it to res
        } else {
            appendToChars(res, &prgm[i]);
        }
    }

    return res;
}


void appendToChars(char* res, char* i)
{
    sprintf(res, "%s%s", res, i);
}
