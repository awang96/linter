/*
** Filename : file_list.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edited : 2018/10/17
**
** Description : Functions to deal with the data struct FileList
*/


#include "file_list.h"

/*** Initialization of a FileList data struct ***/
/** Params **/
/* char *name : filename */
/** Return **/
/* FileList* : an element of a list of filenames */
FileList* initFileList(char* name)
{

    FileList* element;
    if (!name) {
        return NULL;
    }
    element = malloc(sizeof(FileList));
    if (!element) {
        return NULL;
    }
    element->name = malloc(sizeof(char) * strlen(name));
    if (!element->name) {
        free(element);
        return NULL;
    }
    strcpy(element->name, name);
    element->next = NULL;
    return element;

}

/*** Add an element at the end of FileList list ***/
/** Params **/
/* FileList **fl : memory address for the first element of the list
   char *name    : filename to add to the list */
/** Return **/
/* 0 : Success
   1 : Failure */
int addFile(FileList** fl, char* name)
{

    FileList* element;
    FileList* p;
    if (!name) {
        return 1;
    }
    p = *fl;
    // if the list is empty
    if (!p) {
        *fl = initFileList(name);
        return 0;
    }
    // if the list only have one element
    if (!p->next) {
        if (!strcmp(p->name, name)) {
            return 0;
        }
    }
    // else
    while (p->next) {
        if (!strcmp(p->name, name)) {
            return 0;
        }
        p = p->next;
    }
    element = initFileList(name);
    if (!element) {
        return 1;
    }
    p->next = element;
    return 0;

}

/*** Suppression of an element at the beginning of a FileList list ***/
/** Params **/
/* FileList **fl: memory address of the first element of the FileList list */
/** Return **/
/* 0 : Success
   1 : Failure */
int delFile(FileList** fl)
{

    FileList* tmp;
    if (!fl) {
        return 1;
    }
    tmp = *fl;
    *fl = (*fl)->next;
    free(tmp->name);
    free(tmp);
    return 0;

}

/*** Suppression of a list ***/
/** Params **/
/* FileList **fl: memory address of the first element of a FileList list */
/** Return **/
/* 0 : Success
   1 : Failure */
int delFileList(FileList** fl)
{

    if (!fl) {
        return 1;
    }
    while (*fl) {
        if (delFile(fl)) {
            return 1;
        }
    }
    return 0;

}

/*** To show a FileList list in the command prompt ***/
/** Param **/
/* FileList *fl : list to print */
void showFileList(FileList* fl)
{

    FileList* p;
    if (!fl) {
        return;
    }
    p = fl;
    while (p) {
        printf("%s\n", p->name);
        p = p->next;
    }

}

/*** Check if fileName is in fl ***/
/** Param **/
/*char *fileName : name of the file to find
  FileList *fl : list of filenames */
/** Return **/
/* 0 : Success
   1 : Failure */
int isInFileList(char *fileName, FileList *fl){

    FileList *p;
    if(!fileName || !fl)
	return 1;
    p = fl;
    while(p){
	//printf("%s : %s\n", fileName, p->name);
	if(!strcmp(fileName, p->name))
	    return 0;
	p = p->next;
    } 
    return 1;

}
