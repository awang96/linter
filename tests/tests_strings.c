
#include <string.h>

#include "minunit.h"
#include "strings.h"
#include "file_helper.h"


static char* should_remove_comments_from_string()
{
    char* program;
    size_t size = readFileToBuffer("../resources/bad_source.c", &program);
    char* woComments = removeComments(program);
    mu_assert("there should not be any '/*' (1)", strstr(woComments, "/*") == NULL);
    mu_assert("there should not be any '*/' (2)", strstr(woComments, "*/") == NULL);
    mu_assert("there should not be any '//' (3)", strstr(woComments, "//") == NULL);
    printf("File size : %lu\n", size);
    mu_assert("file size should be 6678, or be updated (4)", size == 6678);
    return 0;
}


static char* all_tests()
{
    mu_run_test(should_remove_comments_from_string);
    return 0;
}


mu_run(all_tests)
