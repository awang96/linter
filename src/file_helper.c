/*
** Filename : file_helper.c
**
** Made by : Alexandre WANG, Quentin FANECO, Jacques RIMBAULT
**
** Last edit : 2018/12/10
**
** Description : Functions to read files
*/

#include "file_helper.h"

#define DIR_NAME 5555

size_t readFileToBuffer(char* file, char** buffer)
{
    FILE* fd = fopen(file, "rb");
    if (fd == NULL) {
        return 0;
    }
    int rc = fseek(fd, 0L, SEEK_END);
    if (rc != 0) {
        return 0;
    }
    long offEnd;
    if ((offEnd = ftell(fd)) < 0) {
        return 0;
    }
    size_t size = (size_t) offEnd;
    *buffer = calloc(size + 1, sizeof(char));
    if (*buffer == NULL) {
        return 0;
    }
    rewind(fd);
    if (fread(*buffer, 1, size, fd) != size) {
        free(*buffer);
        return 0;
    }
    if (fclose(fd) == EOF) {
        free(*buffer);
        return 0;
    }
    return size;
}


char* readSourceFileToBufferWithoutComments(char* file)
{
    char* text;
    readFileToBuffer(file, &text);
    return removeComments(text);
}

void parseDir(char *dirName, FileList *fl, RuleList *rl, Error **errors){

    DIR *dir;
    struct dirent *ent;
    char nextDir[DIR_NAME];
    char ext[3];
    char *src;
    if((dir = opendir(dirName))){
	// parsing dirName
	while((ent = readdir(dir))){
	    if(!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || !isInFileList(ent->d_name, fl)){
		continue;
	    }
	    strcpy(ext, ent->d_name + strlen(ent->d_name) - 2);
	    strcpy(nextDir, dirName);
	    strcat(nextDir, "/");
	    strcat(nextDir, ent->d_name);
	    // if ent is a directory, call to parseDir
	    if(ent->d_type == DT_DIR){
		parseDir(nextDir, fl, rl, errors);
	    }
	    // if ent is a file, check extension
	    else if(ent->d_type == DT_REG && (!strcmp(ext, ".c") || !strcmp(ext, ".h"))){
		src = readSourceFileToBufferWithoutComments(nextDir);
		applyRulesBuffer(rl, src, errors, ent->d_name);
		free(src);
	    }
	}
	closedir(dir);
    }

}
