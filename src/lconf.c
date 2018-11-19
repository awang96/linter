/*
** Filename : lconf.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/10/18
**
** Description : Functions to get options from .lconf files
*/

#include "lconf.h"

/*** .lconf file opening ***/
/** Params **/
/* char *path : path to the .lconf file */
/** Return **/
/* FILE* : file handler for the .lconf file */
FILE* openLconf(char *path){

    FILE *f;
    if(!path)
        return NULL;
    if(strcmp(path + strlen(path) - 6, ".lconf"))
        return NULL;
    f = fopen(path, "r");
    if(!f)
        return NULL;
    return f;

}

/*** Parsing of the .lconf file ***/
/** Params **/
/* FILE *conf : file handler for the .lconf file */
/** Return **/
/* Config* : Linter's options in the first .lconf file */
Config* getKey(FILE *conf){

    char tmp[LINE];
    char keyFound[KEY_LEN];
    FileList *extends = NULL;
    FileList *excluded = NULL;
    RuleList *rules = NULL;
    Config *config;
    if(!conf)
        return NULL;
    config = initConfig(extends, rules, excluded, "false");
    if(!config)
        return NULL;
// Parsing through the lines of the .lconf file
    while(fgets(tmp, LINE, conf)){
        if(tmp[0] == '='){
            strcpy(keyFound, tmp + 1);
            if(keyFound[strlen(keyFound) - 1] == '\n')
                keyFound[strlen(keyFound) - 1] = '\0';
            if(checkKey(keyFound)){
                printf("Cl�s erronn�es\n");
                break;
            }
// If a key is found, we'll parse through its values
            while(fgets(tmp, LINE, conf)){
                if(!strcmp(tmp, "\n"))
                    break;
                if(tmp[strlen(tmp) - 1] == '\n')
                    tmp[strlen(tmp) - 1] = '\0';
                if(!strcmp(keyFound, "recursive")){
                    if(!strcmp(tmp, "true"))
                        config->recursive = 1;
                    else
                        config->recursive = 0;
                }
                else{
                    if(fillConf(tmp, keyFound, config, 0) == 1){
                        delConfig(&config);
                        return NULL;
                    }
                }
            }
        }
    }
    getParentLconf(config);
    return config;

}

/*** Fill the Config data struct with the options in the .lconf file ***/
/** Params **/
/* char *line : current line from the .lconf file
   char *key : current key from the .lconf file
   Config *conf : data struct to access the .lconf file options */
/** Return **/
/* 0 : Success
   1 : Failure */
int fillConf(char *line, char *key, Config *conf, unsigned char parent){

    if(!line || !key || !conf)
        return 1;
    if(!strcmp(key, "extends")){
        if(addFile(&(conf->extends), line))
            return 1;
        else
            return 2;
    }
    else if(!strcmp(key, "rules")){
        if(!parent){
            if(addRule(&(conf->rules), line))
                return 1;
        }
        else{
            if(addRuleParent(&(conf->rules), line))
                return 1;
        }
    }
    else if(!strcmp(key, "excludedFiles")){
        if(addFile(&(conf->filesExcluded), line))
            return 1;
    }
    return 0;

}

/*** Check if the key exists or not ***/
/** Params **/
/* char *key : key found in .lconf file */
/** Return **/
/* 0 : Success, key exists
   1 : Failure, key doesn't exist */
int checkKey(char *key){

    char keys[KEY][KEY_LEN] = {"extends", "rules", "excludedFiles", "recursive"};
    int count;
    if(!key)
        return 1;
    for(count = 0; count < KEY; count++){
        if(!strcmp(keys[count], key))
            return 0;
    }
    return 1;

}

/*** Get the options of the parent .lconf files ***/
/** Params **/
/* Config *conf : data structure with the options from the .lconf file */
void getParentLconf(Config *conf){

    FileList *p;
    if(!conf)
        return;
    p = conf->extends;
    while(p){
//        printf("%s\n", p->name);
//        if(parseParent(p->name, conf))
//            p = conf->extends;
        parseParent(p->name, conf);
        p = p->next;
    }

}

/*** Parse the parent .lconf file ***/
/** Params **/
/* char *filename : path to the parent .lconf file
   Config *conf : data structure to stock the .lconf file options */
/** Return **/
/* 0 : Failure
   int : numbers of parent .lconf files added */
int parseParent(char *filename, Config *conf){

    FILE *f;
    char line[LINE];
    char key[KEY_LEN];
    char parse = 0;
    if(!filename || !conf)
        return 0;
    f = openLconf(filename);
    if(!f)
        return 0;
    while(fgets(line, LINE, f)){
        if(line[0] == '='){
            strcpy(key, line + 1);
            if(key[strlen(key) - 1] == '\n')
                key[strlen(key) - 1] = '\0';
            if(checkKey(key)){
                printf("Cl�s erronn�es\n");
                break;
            }
            while(fgets(line, LINE, f)){
                if(!strcmp(line, "\n"))
                    break;
                if(line[strlen(line) - 1] == '\n')
                    line[strlen(line) - 1] = '\0';
                if(fillConf(line, key, conf, 1) == 2){
                    parse++;
                }
            }
        }
    }
    return parse;

}
