/*
** Filename : main.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/10/18
**
** Description : This file contains the main which executes the Linter.
*/

#include <stdio.h>
#include <stdlib.h>

#include "lconf.h"
#include "config.h"
#include "coding_norms.h"
#include "rules.h"
#include "file_helper.h"


Config* getConfig(char* file)
{
    FILE* conf = openLconf(file);
    if (!conf) {
        fprintf(stderr, "Open failed\n");
        return NULL;
    }
    Config* c = getKey(conf);
    printf("=extends\n");
    showFileList(c->extends);
    printf("\n=rules\n");
    showRuleList(c->rules);
    printf("\n=excludedFiles\n");
    showFileList(c->filesExcluded);
    printf("\n=recursive\n%d\n", c->recursive);
    fclose(conf);
    return c;
}


/*** Main ***/
/** Params **/
/* argv[1] : char*, path to the .lconf file */
int main(int argc, char** argv)
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    Config* c = getConfig(argv[1]);
    //printf("ok\n");
    char* source = readSourceFileToBufferWithoutComments("resources/bad_source.c");
    applyRulesBuffer(c->rules, source);
    parseDir("/home/azerty/Documents/programmes/linter", c->filesExcluded);
    // parseDir("/home/azerty/Documents/programmes/linter");
    free(source);
    delConfig(&c);
    return EXIT_SUCCESS;
}
