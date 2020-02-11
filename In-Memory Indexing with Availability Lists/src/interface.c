#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "interface.h"

#define NCMD 3

void initialize() {
    read();
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
        add(command);
    } else if (strcmp(command[0], "find") == 0) {
        find(command);
    } else if (strcmp(command[0], "del") == 0) {
        delete(command);
    } else if (strcmp(command[0], "end") == 0) {
        end(command);
    } else {
        printf("Input Command Error.\n");
    }
}

void add(const char* command[]) {
    int i;
    for (i = 0; i < NCMD; i++) {
        printf("%s\n", command[i]);
    }
}

void find(const char* command[]) {

}

void delete(const char* command[]) {

}

void end(const char* command[]) {
    
}