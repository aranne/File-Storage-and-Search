#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <btree.h>

void read(void);
void parse(char *line);

boolean running = TRUE;

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        printf("Number of arguments error\n");
        return 0;
    }
    const char* filename = argv[1];
    const char* order = argv[2];
    init_btree(filename, order);
    read();
    close_btree();
    return 0;
}

void read() {
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    while (running) {
        if ( (len = getline(&line, &size, stdin)) != EOF) {
            parse(line);
        }
    }
    free(line);
}

void parse(char *line) {
    char* command[3];
    
    int i = 0;
    while ((command[i++] = strsep(&line, " ")) != NULL );
    if (strcmp(command[0], "end\n") == 0 || strcmp(command[0], "end") == 0) {
        running = 0;
    } else if (strcmp(command[0], "add") == 0) {
        int key = atoi(command[1]);
        add(key);
    } else if (strcmp(command[0], "find") == 0) {
        int key = atoi(command[1]);
        search(key, TRUE);
    } else if (strcmp(command[0], "print\n") == 0 || strcmp(command[0], "print") == 0) {
        
    } else {
        printf("Input Command Format Error\n");
    }
}