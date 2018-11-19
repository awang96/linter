/*
** Filename : config.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/10/17
**
** Description : Functions to deal with the data struct Config
*/

#include "../header/config.h"

/*** Initialization of a Config* data struct, which contains the Linter's options ***/
/** Params **/
/* FileList *extends  : list of parent .lconf files
   RuleList *rules    : list of rules
   FileList *excluded : list of files to exclude from the parsed directory
   char *rec          : if the parsing is recursive or not */
/** Return **/
/* Config* : Linter's options after parsing a .lconf file */
Config* initConfig(FileList *extends, RuleList *rules, FileList *excluded, char *rec){

    Config *conf;
    conf = malloc(sizeof(Config));
    if(!conf)
        return NULL;
    conf->extends = extends;
    conf->rules = rules;
    conf->filesExcluded = excluded;
    if(!strcmp(rec, "true"))
        conf->recursive = 1;
    else
        conf->recursive = 0;
    return conf;

}

/*** Suppression of a Config* data struct ***/
/** Params **/
/* Config **config : memory address of a Config* data struct */
/** Return **/
/* 0 : Success
   1 : Failure */
int delConfig(Config **config){

    if(!config)
        return 1;
    if(delFileList(&((*config)->extends)))
        return 1;
    if(delFileList(&((*config)->filesExcluded)))
        return 1;
    if(delRuleList(&((*config)->rules)))
        return 1;
    free(*config);
    return 0;

}
