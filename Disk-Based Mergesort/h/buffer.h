#ifndef buffer_h
#define buffer_h

#define buffer_size 1000

extern int input[buffer_size];
extern int output[buffer_size];
extern int * input_p;
extern int * output_p;
extern int input_size;

void init_buffer(void);
int load_buffer(int size, FILE* fp);
void write_buffer(int* buffer, int size, char* filename);
void sort_buffer(int* buffer, int sort_size);
void print_buffer(int* buffer);

#endif