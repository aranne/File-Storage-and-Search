#ifndef output_h
#define output_h

#include "Array.h"
#include <sys/time.h>

void print_output(const Array* seek, const Array* hit, struct timeval exec);

#endif