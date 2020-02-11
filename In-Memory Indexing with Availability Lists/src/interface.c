#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "db.h"
#include "interface.h"
#include "array.h"
#include "primindex.h"


#define NCMD 3
#define NADD 3
#define NFIND 2
#define NDEL 2
#define NEND 1

const char* mode = NULL;
const char* filename = NULL;
const char* indexname = NULL;
const char* listname = NULL;
Array primindex;

void initialize(const char* m, const char* fn) {
    mode = m;
    filename = fn;
    initDB();
    primindex = loadindex();
    read();
    writeindex(&primindex);
}

void initDB() {
    if (strcmp(mode, "--first-fit") == 0) {
        indexname = "firstindex.bin";
        listname = "firstlist.bin";
    } else if (strcmp(mode, "--best-fit") == 0) {
        indexname = "bestindex.bin";
        listname = "bestlist.bin";
    } else if (strcmp(mode, "--worst-fit") == 0) {
        indexname = "worstindex.bin";
        listname = "worstlist.bin";
    } else {
        printf("Input Mode Error\n");
    }
}

void read() {
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    while ((len = getline(&line, &size, stdin)) != EOF) {
        parse(line);
    }

    free(line);
}

void parse(char * line) {
    char *token = NULL;
    const char* command[NCMD];
    
    int i = 0;
    token = strtok(line, " ");
    while (token != NULL && i < NCMD) {
        command[i++] = token;
        token = strtok(NULL, " ");
    }

    if (strcmp(command[0], "add") == 0) {
        addR(command);
    } else if (strcmp(command[0], "find") == 0) {
        findR(command);
    } else if (strcmp(command[0], "del") == 0) {
        deleteR(command);
    } else if (strcmp(command[0], "end") == 0) {
        end(command);
    } else {
        printf("Input Command Error.\n");
    }
}

void addR(const char* command[]) {
    int i;
    for (i = 0; i < NADD; i++) {
        
    }
}

void findR(const char* command[]) {

}

void deleteR(const char* command[]) {

}

void end(const char* command[]) {

}