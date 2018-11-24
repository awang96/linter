
#include <stdio.h>
#include <stdlib.h>

#include "file_helper.h"
#include "strings.h"


size_t readFileToBuffer(char* file, char** buffer)
{
    FILE* fd = fopen(file, "rb");
    if (fd == NULL) {
        return 0;
    }
    int rc = fseek(fd, 0L, SEEK_END);
    if (rc != 0) {
        return 0;
    }
    long offEnd;
    if ((offEnd = ftell(fd)) < 0) {
        return 0;
    }
    size_t size = (size_t) offEnd;
    *buffer = calloc(size + 1, sizeof(char));
    if (*buffer == NULL) {
        return 0;
    }
    rewind(fd);
    if (fread(*buffer, 1, size, fd) != size) {
        free(*buffer);
        return 0;
    }
    if (fclose(fd) == EOF) {
        free(*buffer);
        return 0;
    }
    return size;
}


char* readSourceFileToBufferWithoutComments(char* file)
{
    char* text;
    readFileToBuffer(file, &text);
    return removeComments(text);
}
