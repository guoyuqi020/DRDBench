extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

int x=1;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* thr1(void* arg) {
  pthread_mutex_lock(&m); // m=0 /\ m'=1
  x = 0;
  x = 1;
  assert(x>=1);
  pthread_mutex_unlock(&m);

  return 0;
}

int main()
{
  pthread_t t;

  while(1) pthread_create(&t, 0, thr1, 0);
}

