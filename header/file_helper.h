#ifndef LINTER_FILE_H
#define LINTER_FILE_H

#include <stdio.h>


/**
 * Read the given file into the given buffer
 * Returns the actual file size (and buffer size)
 * (buffer will be allocated)
 * @param file
 * @param buffer
 * @return buffer size
 */
size_t readFileToBuffer(char* file, char** buffer);

#endif //LINTER_FILE_H
