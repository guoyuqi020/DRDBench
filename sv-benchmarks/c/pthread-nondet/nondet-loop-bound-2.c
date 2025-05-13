#include <pthread.h>
extern void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }
unsigned int __VERIFIER_nondet_uint();
extern void abort(void); 
void assume_abort_if_not(int cond) { 
  if(!cond) {abort();}
}
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

#undef assert
#define assert( X ) __VERIFIER_assert(X)

volatile int x;
volatile int n;

void* thr1(void* arg) {
    assert(x <= n);
}

void* thr2(void* arg) {
    int t;
    t = x;
    x = t + 1;
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    int i;
    x = 0;
    n = __VERIFIER_nondet_uint();
    assume_abort_if_not(n >= 20 && n < 40);
    pthread_create(&t1, 0, thr1, 0);
    for (i = 0; i < n; i++) {
	     pthread_create(&t2, 0, thr2, 0);
    }
    return 0;
}
