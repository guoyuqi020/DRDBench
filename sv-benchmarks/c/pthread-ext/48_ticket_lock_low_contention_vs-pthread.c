extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);
extern int __VERIFIER_nondet_int(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;
unsigned c = 0;
void* thr1(void* arg)
{
  pthread_mutex_lock(&s);
  c = 1; assert(c == 1); c = 0;
  pthread_mutex_unlock(&s);

  return 0;
}

int main()
{
  pthread_t t;

  while(__VERIFIER_nondet_int()) pthread_create(&t, 0, thr1, 0);
  thr1(0);

  return 0;
}

