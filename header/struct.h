/*
** Filename : struct.h
**
** Made by : Alexandre WANG
**
** Last edit : 2018/10/17 by Alexandre WANG
**
** Description : Header for struct.c
*/

#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

/*** String linked list for filenames ***/
/** char *name : filename
    struct fileList *next : ptr for the next element of the list **/
typedef struct fileList
{

    char* name;
    struct fileList* next;

} FileList;

/*** Linked list for the rules ***/
/** char *name : name of the rule
    unsigned int value : value of the rule
    struct ruleList *next : ptr for the next element of the list **/
typedef struct ruleList
{

    char* name;
    unsigned int value;
    struct ruleList* next;

} RuleList;

/*** Data structure to access the data obtained through the .lconf files ***/
/** FileList *extends : Linked list of .lconf filenames
    RuleList *rules : Linked list of rules
    FileList *filesExcluded : Linked list of filenames which are excluded from the parsing
    unsigned char recursive : if the parsing is recursive or not **/
typedef struct config
{

    FileList* extends;
    RuleList* rules;
    FileList* filesExcluded;
    unsigned char recursive;

} Config;

/*** Data structure to list errors in files ***/
/** unsigned int line : line number of the error
    char *errorname : name of the rule
    char *filename : name of the file
    struct error *next : pointer to the next error **/
typedef struct error
{

    unsigned int line;
    char* errorName;
    char* filename;
    struct error* next;

} Error;

/*** Data structure to list variables declared in files ***/
/** char *type : type of the variable
    char *name : name of the variable
    unsigned char used : boolean to check if the variable is used or not
    struct variables *next : pointer to the next variable **/
typedef struct variables
{

    char* type;
    char* name;
    unsigned char used;
    struct variables* next;

} Variables;

#endif // STRUCT_H
