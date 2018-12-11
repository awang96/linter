/*
** Filename : file_list.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/17 by Alexandre WANG
**
** Description : Header for file_list.c
*/

#ifndef FILE_LIST_H
#define FILE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <string.h>


FileList* initFileList(char* name);
int addFile(FileList** fl, char* name);
int delFile(FileList** fl);
int delFileList(FileList** fl);
void showFileList(FileList* fl);
int isInFileList(char *fileName, FileList *fl);

#endif // FILE_LIST_H
