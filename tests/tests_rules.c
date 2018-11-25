
#include <stdio.h>
#include <stdbool.h>

#include "minunit.h"
#include "rules.h"


static char* expect_bad_variable_declaration()
{
    char* declaration[] = {
        "int a", // missing semicolon
        "int 1", // invalid variable name
        "char c = \"h\"", // double quote -> not a char
        "char* uuu = 'd'", // single quote -> invalid
        "int a = ;", // missing right side
    };
    for (int i = 0; i < 5; i += 1) {
        mu_assert(
            "should be an invalid declaration",
            isValidVariableDeclaration(declaration[i]) == false
        );
    }
    return 0;
}


static char* all_tests()
{
    mu_run_test(expect_bad_variable_declaration);
    return 0;
}


mu_run(all_tests);
