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

/*** Main ***/
/** Params **/
/* argv[1] : char*, path to the .lconf file */
int main(int argc, char** argv)
{
    FILE* conf;
    Config* c;
    if (argc < 1) {
        return EXIT_FAILURE;
    }
    conf = openLconf(argv[1]);
    if (!conf) {
        printf("Open failed\n");
        return EXIT_FAILURE;
    }
    c = getKey(conf);
    printf("=extends\n");
    showFileList(c->extends);
    printf("\n=rules\n");
    showRuleList(c->rules);
    printf("\n=excludedFiles\n");
    showFileList(c->filesExcluded);
    printf("\n=recursive\n%d\n", c->recursive);
    fclose(conf);
    conf = fopen("src/coding_norms.c", "r");
    if (!conf) {
        fprintf(stderr, "couldn't open file");
        return EXIT_FAILURE;
    }
    // if (!commentsHeader(conf)) {
    //     printf("OK\n");
    // } else {
    //     printf("KO\n");
    // }
    applyRules(c->rules, conf);
    fclose(conf);
    delConfig(&c);
    return EXIT_SUCCESS;
}
