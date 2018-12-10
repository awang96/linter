#include "error.h"


Error* initError(unsigned int line, char* errorName, char* filename) {

    Error* error;
    if (!errorName || !filename) {
        return NULL;
    }
    error = malloc(sizeof(Error));
    if (!error) {
        return NULL;
    }

    strcpy(error->errorName, errorName);
    strcpy(error->filename, filename);
    error->line = line;
    error->next = NULL;

    return error;
}

int addError(Error** el, unsigned int line, char* errorName, char* filename) {

    Error* element;
    Error* p;

    if (!errorName || !filename) {
        return 1;
    }

    p = *el;
    if (!p) {
        *el = initError(line, errorName, filename);
        return 0;
    }

    while (p->next) {
        p = p->next;
    }

    element = initError(line, errorName, filename);
    if (!element) {
        return 1;
    }
    p->next = element;
    return 0;

}


int delErrorList(Error** error) {

    if (!error) {
        return 1;
    }
    while (*error) {
        if (delError(error)) {
            return 1;
        }
    }
    return 0;
}

int delError(Error** el) {

    Error* tmp;
    if (!el) {
        return 1;
    }
    tmp = *el;
    *el = (*el)->next;
    free(tmp->filename);
    free(tmp->errorName);
    free(tmp);
    return 0;

}
