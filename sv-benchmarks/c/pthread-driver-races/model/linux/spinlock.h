#ifndef __LINUX_SPINLOCK_H
#define __LINUX_SPINLOCK_H

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

#ifndef SPIN_LOCK_UNINITIALIZED
#define SPIN_LOCK_UNINITIALIZED 0
#endif

#ifndef SPIN_LOCK_INITIALIZED
#define SPIN_LOCK_INITIALIZED 1
#endif

#ifndef SPIN_LOCK_UNLOCKED
#define SPIN_LOCK_UNLOCKED 0
#endif

#ifndef SPIN_LOCK_LOCKED
#define SPIN_LOCK_LOCKED 1
#endif

typedef struct
{
  int init;
  int lock;
} spinlock_t;

#define DEFINE_SPINLOCK(x) spinlock_t x = { SPIN_LOCK_INITIALIZED, SPIN_LOCK_UNLOCKED }

void spin_lock_init(spinlock_t *lock)
{
  lock->init = SPIN_LOCK_INITIALIZED;
  lock->lock = SPIN_LOCK_UNLOCKED;
}

void spin_lock(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid != lock->lock);
  __VERIFIER_atomic_begin();
  assume_abort_if_not(lock->lock == SPIN_LOCK_UNLOCKED);
  lock->lock = SPIN_LOCK_LOCKED;
  __VERIFIER_atomic_end();
}

void spin_lock_irqsave(spinlock_t *lock, unsigned long value)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid != lock->lock);
  __VERIFIER_atomic_begin();
  assume_abort_if_not(lock->lock == SPIN_LOCK_UNLOCKED);
  lock->lock = SPIN_LOCK_LOCKED;
  __VERIFIER_atomic_end();
}

void spin_lock_irq(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid != lock->lock);
  __VERIFIER_atomic_begin();
  assume_abort_if_not(lock->lock == SPIN_LOCK_UNLOCKED);
  lock->lock = SPIN_LOCK_LOCKED;
  __VERIFIER_atomic_end();
}

void spin_lock_bh(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid != lock->lock);
  __VERIFIER_atomic_begin();
  assume_abort_if_not(lock->lock == SPIN_LOCK_UNLOCKED);
  lock->lock = SPIN_LOCK_LOCKED;
  __VERIFIER_atomic_end();
}

void spin_unlock(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid == lock->lock);
  __VERIFIER_atomic_begin();
  lock->lock = SPIN_LOCK_UNLOCKED;
  __VERIFIER_atomic_end();
}

void spin_unlock_irqrestore(spinlock_t *lock, unsigned long value)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid == lock->lock);
  __VERIFIER_atomic_begin();
  lock->lock = SPIN_LOCK_UNLOCKED;
  __VERIFIER_atomic_end();
}

void spin_unlock_irq(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid == lock->lock);
  __VERIFIER_atomic_begin();
  lock->lock = SPIN_LOCK_UNLOCKED;
  __VERIFIER_atomic_end();
}

void spin_unlock_bh(spinlock_t *lock)
{
  //pthread_t tid = pthread_self();
  //__VERIFIER_assert(tid == lock->lock);
  __VERIFIER_atomic_begin();
  lock->lock = SPIN_LOCK_UNLOCKED;
  __VERIFIER_atomic_end();
}

#endif /* __LINUX_SPINLOCK_H */
