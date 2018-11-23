/*
** Filename : variables.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/11/08
**
** Description : Functions to deal with Variables data structures
*/

#include "variables.h"

/*** Initialization of a Variables data structure ***/
/** Params **/
/* char *type : type of the variable
   char *name*/
Variables* initVariables(char* type, char* name)
{

    Variables* element;
    if (!type || !name) {
        return NULL;
    }
    element = malloc(sizeof(Variables));
    if (!element) {
        return NULL;
    }
    element->type = malloc(sizeof(char) * strlen(type));
    if (!element->type) {
        free(element);
        return NULL;
    }
    element->name = malloc(sizeof(char) * strlen(name));
    if (!element->name) {
        free(element->type);
        free(element);
        return NULL;
    }
    strcpy(element->type, type);
    strcpy(element->name, name);
    element->used = 0;
    return element;

}

/*** Add an element at the end of the list ***/
/** Params **/
/* Variables **variableList : list of variables
   char *name : name of the variable
   char *type : type of the variable */
/** Return **/
/* 0 : Success
   1 : Failure */
int addVariable(Variables** variableList, char* name, char* type)
{

    Variables* p;
    if (!variableList || !name || !type) {
        return 1;
    }
    p = *variableList;
    if (!p) {
        *variableList = initVariables(type, name);
        if (!variableList) {
            return 1;
        }
        return 0;
    }
    while (p->next) {
        p = p->next;
    }
    p->next = initVariables(type, name);
    if (!p->next) {
        return 1;
    }
    return 0;

}

/*** Remove last element from list ***/
/** Params **/
/* Variables **variableList : list of Variables */
/** Return **/
/* 0 : Success
   1 : Failure */
int delVariable(Variables** variableList)
{

    Variables* p;
    if (!variableList) {
        return 1;
    }
    p = *variableList;
    *variableList = (*variableList)->next;
    free(p->name);
    free(p->type);
    free(p);
    return 0;

}

/*** Suppression of a list ***/
/** Params **/
/* Variables **fl: memory address of the first element of a Variables list */
/** Return **/
/* 0 : Success
   1 : Failure */
int delVariableList(Variables** variableList)
{

    if (!variableList) {
        return 1;
    }
    while (*variableList) {
        if (delVariable(variableList)) {
            return 1;
        }
    }
    return 0;

}
