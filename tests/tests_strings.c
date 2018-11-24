
#include <string.h>
#include <stdlib.h>

#include "minunit.h"
#include "strings.h"
#include "file_helper.h"


char* BAD_SOURCE = "../resources/bad_source.c";


static char* should_remove_comments_from_string()
{
    char* program;
    size_t size = readFileToBuffer(BAD_SOURCE, &program);
    char* woComments = removeComments(program);
    mu_assert("there should not be any '/*' (1)", strstr(woComments, "/*") == NULL);
    mu_assert("there should not be any '*/' (2)", strstr(woComments, "*/") == NULL);
    mu_assert("there should not be any '//' (3)", strstr(woComments, "//") == NULL);
    mu_assert("should contain '/*' (4)", strstr(program, "/*") != NULL);
    mu_assert("should contain '*/' (5)", strstr(program, "*/") != NULL);
    mu_assert("should contain '//' (6)", strstr(program, "//") != NULL);
    printf("File size : %lu\n", size);
    mu_assert("file size should be 6678, or be updated (4)", size == 6678);
    free(program);
    free(woComments);
    return 0;
}


static char* should_read_directly_without_comments()
{
    char* program = readSourceFileToBufferWithoutComments(BAD_SOURCE);
    mu_assert("there should not be any '/*' (1)", strstr(program, "/*") == NULL);
    mu_assert("there should not be any '*/' (2)", strstr(program, "*/") == NULL);
    mu_assert("there should not be any '//' (3)", strstr(program, "//") == NULL);
    free(program);
    return 0;
}


static char* all_tests()
{
    mu_run_test(should_remove_comments_from_string);
    mu_run_test(should_read_directly_without_comments);
    return 0;
}


mu_run(all_tests)
