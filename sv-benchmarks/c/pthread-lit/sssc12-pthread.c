// Source: Alejandro Sanchez, Sriram Sankaranarayanan, Cesar Sanchez, Bor-Yuh
// Evan Chang: "Invariant Generation for Paramterized Systems using
// Self-Reflection", SAS 2012

#include <pthread.h>
#include <stdlib.h>
#include "assert.h"

int *data;
volatile int len;
volatile int next;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* thr(void* arg) {
    int c, end;
    c = 0;
    end = 0;
    
    pthread_mutex_lock(&lock);
    if (next + 10 <= len) {
	c = next;
	next = end = next + 10;
    }
    pthread_mutex_unlock(&lock);
    while (c < end) {
	__VERIFIER_assert(0 <= c && c < len);
	data[c] = 0;
	c = c + 1;
    }
    return 0;
}

int main() {
    pthread_t t;
    next = 0;
    len = __VERIFIER_nondet_int();
    assume_abort_if_not(len > 0 && len < 4294967296 / sizeof(int));
    data = malloc(sizeof(int) * len);
    while(1) {
	pthread_create(&t, 0, thr, 0);
    }
    return 0;
}
