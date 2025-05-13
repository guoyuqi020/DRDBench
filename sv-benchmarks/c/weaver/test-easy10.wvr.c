// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2021 F. Schuessele <schuessf@informatik.uni-freiburg.de>
// SPDX-FileCopyrightText: 2021 D. Klumpp <klumpp@informatik.uni-freiburg.de>
//
// SPDX-License-Identifier: LicenseRef-BSD-3-Clause-Attribution-Vandikas

typedef unsigned long int pthread_t;

union pthread_attr_t
{
  char __size[36];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;

extern void __assert_fail(const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
void reach_error() { __assert_fail("0", "test-easy10.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern unsigned int  __VERIFIER_nondet_uint(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

unsigned int x1, x2, y1, y2;
_Bool t11, t12, t21, t22, f11, f12, f21, f22;

void* thread1(void* _argptr) {
  __VERIFIER_atomic_begin();
  t11 = x1 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x1 = t11;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  f11 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(f11 && f21);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  t11 = y1 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y1 = t11;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  t21 = y1 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y1 = t21;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  f21 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(f11 && f21);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  t21 = x1 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x1 = t21;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  t12 = x2 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x2 = t12;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  f12 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(f12 && f22);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  t12 = y2 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y2 = t12;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread4(void* _argptr) {
  __VERIFIER_atomic_begin();
  t22 = y2 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y2 = t22;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  f22 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(f12 && f22);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  t22 = x2 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x2 = t22;
  __VERIFIER_atomic_end();

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;
  
  x1 = __VERIFIER_nondet_uint();
  x2 = __VERIFIER_nondet_uint();
  y1 = __VERIFIER_nondet_uint();
  y2 = __VERIFIER_nondet_uint();
  assume_abort_if_not(x1 == x2 && y1 == y2);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);

  assume_abort_if_not(x1 != x2 || y1 != y2);
  reach_error();

  return 0;
}
