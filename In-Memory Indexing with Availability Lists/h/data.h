#ifndef data_h
#define data_h

FILE* load_data(void);
void write_data(FILE* fp);
void add_record(const char* key, const char* record);
int find_record(const char* keystr);
char* read_record(long offset);
long write_record(long offset, int len, const char* record);
int delete_record(const char* keystr);
#endif