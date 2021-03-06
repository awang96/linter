#ifndef LINTER_MINUNIT_H
#define LINTER_MINUNIT_H

#include <stdio.h>


#define mu_assert(message, test) \
    do { \
        if (!(test)) return message; \
    } while (0)

#define mu_run_test(test) \
    do { \
        char *message = test(); \
        if (message) return message; \
        tests_run++; \
    } while (0)

#define mu_run(tests) \
    int tests_run = 0; \
    int main() \
    { \
        char* result = tests(); \
        if (result != 0) { \
            fprintf(stderr, "Error, %s\n", result); \
        } else { \
            printf("All tests passed\n"); \
        } \
        printf("Tests run: %d\n", tests_run); \
        return result != 0; \
    }

extern int tests_run;

#endif //LINTER_MINUNIT_H
