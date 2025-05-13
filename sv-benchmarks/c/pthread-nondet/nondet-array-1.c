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

#define SIZE 10
int a[SIZE] = {0};
int x = 0;

void *thr(void* arg) {
  int t = x;
  a[t] = 1;
  x = t + 1;
}

int main(int argc, char* argv[]) {
  pthread_t t[SIZE];
  int i;
  int n = __VERIFIER_nondet_uint();
  assume_abort_if_not(n >= SIZE/2 && n <= SIZE);

  for (i = 0; i < n; i++) {
    pthread_create(&t[i], 0, thr, 0);
  }
  for (i = 0; i < n; i++) {
    pthread_join(t[i], NULL);
  }
  int sum = 0;
  for (i = 0; i < n; i++) {
    sum += a[i];
  }
  assert(sum == SIZE - 1);
  return 0;
}
