/*
** filename : rule_list.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edited : 2018/10/18
**
** Description : Functions to deal with RuleList data struct
*/

#include "../header/rule_list.h"

/*** Initialization of a RuleList list element ***/
/** Params **/
/* char *name : name of the rule
   char *value : value of the rule */
/** Return **/
/* RuleList* : a RuleList list element */
RuleList* initRuleList(char *name, char *value){

    RuleList *rule;
    if(!name || !value)
        return NULL;
    rule = malloc(sizeof(RuleList));
    if(!rule)
        return NULL;
    rule->name = name;
    rule->value = assignValue(value);
    free(value);
    rule->next = NULL;
    return rule;

}

/*** Determines the value of the rule ***/
/** Params **/
/* char *value: String, value of the rule (on, off or n) */
/** Return **/
/* unsigned int : value of the rule (0 => off, 1 => on or n) */
unsigned int assignValue(char *value){

    if(!value)
        return 0;
    if(!strcmp(value, "on"))
        return 1;
    else if(!strcmp(value, "off"))
        return 0;
    else{
        return atoi(value);
    }

}

/*** Adds a RuleList element at the end of a RuleList list ***/
/** Params **/
/* RuleList **rl : memory address of the first element of a RuleList list
   char *line    : line with the name and the value of the rule */
/** Return **/
/* 0 : Success
   1 : Failure */
int addRule(RuleList **rl, char *line){

    RuleList *element;
    RuleList *p;
    char *name;
    char *value;
    if(!line)
        return 1;
    name = malloc(sizeof(char) * strlen(line));
    if(!name)
        return 1;
    value = malloc(sizeof(char) * strlen(line));
    if(!value){
        free(name);
        return 1;
    }
    if(setNameValue(line, name, value)){
        free(name);
        free(value);
        return 1;
    }
    p = *rl;
    if(!p){
        *rl = initRuleList(name, value);
        return 0;
    }
    if(!p->next){
        if(!strcmp(p->name, name)){
            p->value = assignValue(value);
            free(name);
            free(value);
            return 0;
        }
    }
    while(p->next){
        if(!strcmp(p->name, name)){
            p->value = assignValue(value);
            free(name);
            free(value);
            return 0;
        }
        p = p->next;
    }
    if(!strcmp(p->name, name)){
        p->value = assignValue(value);
        free(name);
        free(value);
        return 0;
    }
    element = initRuleList(name, value);
    if(!element)
        return 1;
    p->next = element;
    return 0;

}

int addRuleParent(RuleList **rl, char *line){

    RuleList *element;
    RuleList *p;
    char *name;
    char *value;
    if(!line)
        return 1;
    name = malloc(sizeof(char) * strlen(line));
    if(!name)
        return 1;
    value = malloc(sizeof(char) * strlen(line));
    if(!value){
        free(name);
        return 1;
    }
    if(setNameValue(line, name, value)){
        free(name);
        free(value);
        return 1;
    }
    p = *rl;
    if(!p){
        *rl = initRuleList(name, value);
        return 0;
    }
    if(!p->next){
        if(!strcmp(p->name, name)){
            free(name);
            free(value);
            return 0;
        }
    }
    while(p->next){
        if(!strcmp(p->name, name)){
            free(name);
            free(value);
            return 0;
        }
        p = p->next;
    }
    if(!strcmp(p->name, name)){
        free(name);
        free(value);
        return 0;
    }
    element = initRuleList(name, value);
    if(!element)
        return 1;
    p->next = element;
    return 0;

}

/*** Suppression of a RuleList element at the beginning of a RuleList list ***/
/** Params **/
/* RuleList **rl: memory address of the first element of a RuleList list */
/** Return **/
/* 0 : Success
   1 : Failure */
int delRule(RuleList **rl){

    RuleList *tmp;
    if(!rl)
        return 1;
    tmp = *rl;
    *rl = (*rl)->next;
    free(tmp->name);
    free(tmp);
    return 0;

}

/*** Suppression of a RuleList list ***/
/** Params **/
/* RuleList **rl: memory address of the first element of a RuleList list */
/** Return **/
/* 0 : Success
   1 : Failure */
int delRuleList(RuleList **rl){

    if(!rl)
        return 1;
    while(*rl){
        if(delRule(rl))
            return 1;
    }
    return 0;

}

/*** Shows a RuleList on the command prompt ***/
/** Param **/
/* RuleList *rl : RuleList list to print */
void showRuleList(RuleList *rl){

    RuleList *p;
    if(!rl)
        return;
    p = rl;
    while(p){
        printf("- %s=%u\n", p->name, p->value); // - ruleName=valueRule
        p = p->next;
    }

}

/*** Separate the name and value of the rule ***/
/** Params **/
/* char *line : line from the .lconf file
   char *name : String where the name will be stocked
   char *value : String where the value will be stocked */
/** Return **/
/* 0 : Success
   1 : Failure */
int setNameValue(char *line, char *name, char *value){

    char *index;
    char *index2;
    if(!line || !name || !value)
        return 1;
// looking for the name of the rule
    index = strchr(line, ' ');
    index++;
    index2 = strchr(index, '=');
    strncpy(name, index, strlen(index) - strlen(index2));
    name[strlen(index) - strlen(index2)] = '\0';
// looking for the value of the rule
    index = index2 + 1;
    strcpy(value, index);
    return 0;

}
