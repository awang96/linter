
#include <string.h>

#include "minunit.h"
#include "strings.h"


static char* should_remove_comments_from_string()
{
    char* program = "/**\n"
                    " * A top comment\n"
                    " */\n"
                    "\n"
                    "// inline comment\n"
                    "unknown_variable /* weird comment */ = 7; // inline comment\n"
                    "\n"
                    "/**\n"
                    " * Comment above function\n"
                    " * a bit longer\n"
                    " * @return\n"
                    " */\n"
                    "unknown_function/* weird comment */() {\n"
                    "    /* weird comment */return;\n"
                    "}\n"
                    "\n"
                    "int good_global = /* weird comment */ 0;\n"
                    "\n"
                    "int good_function() {\n"
                    "    return /*comment*/ 0;\n"
                    "}";
    char* woComments = removeComments(program);
    mu_assert("there should not be any '/*' (1)", strstr(woComments, "/*") == NULL);
    mu_assert("there should not be any '*/' (2)", strstr(woComments, "*/") == NULL);
    mu_assert("there should not be any '//' (3)", strstr(woComments, "//") == NULL);
    return 0;
}


static char* all_tests()
{
    mu_run_test(should_remove_comments_from_string);
    return 0;
}


mu_run(all_tests)
