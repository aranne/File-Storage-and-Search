#ifndef time_h
#define time_h

#include <sys/time.h>

void timeval_subtract(struct timeval* result, struct timeval* x, struct timeval* y);

#endif