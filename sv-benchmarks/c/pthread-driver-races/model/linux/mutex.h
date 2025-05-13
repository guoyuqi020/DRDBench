#ifndef __LINUX_MUTEX_H
#define __LINUX_MUTEX_H


#include <pthread.h>
#include <linux/types.h>

extern _Bool __VERIFIER_nondet_bool(void);
extern char __VERIFIER_nondet_char(void);
extern uint __VERIFIER_nondet_uint(void);
extern int __VERIFIER_nondet_int(void);
extern ulong __VERIFIER_nondet_ulong(void);
extern long __VERIFIER_nondet_long(void);

extern void __VERIFIER_atomic_begin(void);

extern void __VERIFIER_atomic_end(void);

extern void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

extern void abort(void); 
void assume_abort_if_not(int cond) { 
  if(!cond) {abort();}
}

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: {reach_error();abort();}
  }
  return;
}

#ifndef MUTEX_UNINITIALIZED
#define MUTEX_UNINITIALIZED 0
#endif

#ifndef MUTEX_INITIALIZED
#define MUTEX_INITIALIZED 1
#endif

#ifndef MUTEX_UNLOCKED
#define MUTEX_UNLOCKED 0
#endif

#ifndef MUTEX_LOCKED
#define MUTEX_LOCKED 1
#endif

struct mutex
{
  int init;
  int locked;
};


#define DEFINE_MUTEX(x) struct mutex x = { MUTEX_INITIALIZED, MUTEX_UNLOCKED }

void mutex_init(struct mutex *lock)
{
  lock->locked = MUTEX_UNLOCKED;
  lock->init = MUTEX_INITIALIZED;
}

void mutex_lock(struct mutex *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid != lock->locked);
  __VERIFIER_atomic_begin();
  assume_abort_if_not(lock->locked == MUTEX_UNLOCKED);
  lock->locked = MUTEX_LOCKED;
  __VERIFIER_atomic_end();
}

bool mutex_lock_interruptible(struct mutex *lock)
{
  bool ret = __VERIFIER_nondet_bool();
  if(!ret) {
    //pthread_t tid = pthread_self();
    //__VERIFIER_assert(tid != lock->locked);
    __VERIFIER_atomic_begin();
    assume_abort_if_not(lock->locked == MUTEX_UNLOCKED);
    lock->locked = MUTEX_LOCKED;
    __VERIFIER_atomic_end();
  }
  return ret;
}

void mutex_unlock(struct mutex *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid == lock->locked);
  __VERIFIER_atomic_begin();
  lock->locked = MUTEX_UNLOCKED;
  __VERIFIER_atomic_end();
}

#endif
