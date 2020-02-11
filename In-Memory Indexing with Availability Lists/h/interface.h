#ifndef interface_h
#define interface_h

void initialize();
void read();
void parse(char * line);

void add(const char* command[]);
void find(const char* command[]);
void delete(const char* command[]);
void end(const char* command[]);

#endif