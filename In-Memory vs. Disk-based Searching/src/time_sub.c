#include <stdio.h>
#include <sys/time.h>
#include "time_sub.h"

// referrence from "Elapsed Time (The GNU C Library)" 
// Link: https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html

void timeval_subtract(struct timeval* result, struct timeval* x, struct timeval* y) {
  /* Perform the carry for the later subtraction by updating y. */  
  if (x->tv_usec < y->tv_usec) {  
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;  
    y->tv_usec -= 1000000 * nsec;  
    y->tv_sec += nsec;  
  }  
  if (x->tv_usec - y->tv_usec > 1000000) {  
    int nsec = (y->tv_usec - x->tv_usec) / 1000000;  
    y->tv_usec += 1000000 * nsec;  
    y->tv_sec -= nsec;  
  }  

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */  
  result->tv_sec = x->tv_sec - y->tv_sec;  
  result->tv_usec = x->tv_usec - y->tv_usec; 
}