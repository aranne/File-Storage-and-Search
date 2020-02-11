#ifndef interface_h
#define interface_h

void initialize(const char* m, const char* fn);
void initDB(const char* m, const char* fn);
void read();
void parse(char * line);

void addR(const char* command[]);
void findR(const char* command[]);
void deleteR(const char* command[]);
void end(const char* command[]);

#endif