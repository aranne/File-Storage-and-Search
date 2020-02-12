#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "db.h"
#include "interface.h"
#include "primindex.h"
#include "holelist.h"
#include "data.h"


#define NCMD 3
#define NADD 3
#define NFIND 2
#define NDEL 2
#define NEND 1

const char* mode = NULL;
const char* filename = NULL;
const char* indexname = NULL;
const char* listname = NULL;
int running;             /* program running flag */
Array     primindex;     /* primary key index */
ArrayList holelist;      /* hole availability list */
FILE* dbfp;              /* file pointer for data file */

void initialize(const char* m, const char* fn) {
    initDB(m, fn);
    loading();
}

void initDB(const char* m, const char* fn) {
    running = 1;
    mode = m;
    filename = fn;
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

void loading() {
    dbfp = load_data();
    holelist = load_holelist();
    primindex = load_index();
}

void writing() {
    write_data(dbfp);
    write_holelist(&holelist);
    write_index(&primindex);
}

void read() {
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    while (running) {
        while ((len = getline(&line, &size, stdin)) != EOF) {
            parse(line);
        }
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
        // findR(command);
    } else if (strcmp(command[0], "del") == 0) {
        // deleteR(command);
    } else if (strcmp(command[0], "end") == 0) {
        end();
    } else {
        printf("Input Command Error.\n");
    }
}

void addR(const char* command[]) {
    add_record(command[1], command[2]);
}

void findR(const char* command[]) {
    find_record(command[1]);
}

void deleteR(const char* command[]) {
    delete_record(command[1]);
}

void end() {
    running = 0;
    printindex(&primindex);
    print_holelist(&holelist);
    writing();
}