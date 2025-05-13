extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

int x, y;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* thr1(void* arg) { //writer
  pthread_rwlock_wrlock(&rwlock);
  x = 3;
  pthread_rwlock_unlock(&rwlock);
  return 0;
}

void* thr2(void* arg) { //reader
  pthread_rwlock_rdlock(&rwlock);
  __VERIFIER_atomic_begin();
  int l = x;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y = l;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  int ly = y;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  int lx = x;
  __VERIFIER_atomic_end();
  assert(ly == lx);
  pthread_rwlock_unlock(&rwlock);
  return 0;
}

int main()
{
  pthread_t t;

  pthread_create(&t, 0, thr1, 0);
  thr2(0);

  return 0;
}

