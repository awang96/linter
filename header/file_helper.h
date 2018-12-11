/*
** Filename : file_helper.h
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/12/10
**
** Description : Header file for file_helper.h
*/

#ifndef LINTER_FILE_H
#define LINTER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "strings.h"
#include "file_list.h"
#include "rules.h"
#include "rule_list.h"
#include "error.h"
#include "coding_norms.h"

/**
 * Read the given file into the given buffer
 * Returns the actual file size (and buffer size)
 * (buffer will be allocated)
 * @param file
 * @param buffer
 * @return buffer size
 */
size_t readFileToBuffer(char* file, char** buffer);

/**
 * Reads a file into an array of char directly
 * without any comments
 * @param file path
 * @return
 */
char* readSourceFileToBufferWithoutComments(char* file);

/**
 * Recursive parsing of a directory
 * @param dirName : path of the directory to parse
 * @return
*/
void parseDir(char *dirName, FileList *fl, RuleList *rl, Error **e);

#endif //LINTER_FILE_H
