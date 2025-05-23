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
void reach_error() { __assert_fail("0", "parallel-ticket-3.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int   __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void  __VERIFIER_atomic_begin();
extern void  __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int m1, m2, m3, s, t, x;
_Bool b;

void* thread1(void* _argptr) {
  __VERIFIER_atomic_begin();
  m1 = t;
  t++;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not( m1 <= s );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x = 0;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  s++;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  m2 = t;
  t++;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not( m2 <= s );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  b = b || x == 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  s++;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  m3 = t;
  t++;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not( m3 <= s );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  b = b || x == 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  s++;
  __VERIFIER_atomic_end();

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  // initialize global variables
  m1 = __VERIFIER_nondet_int();
  m2 = __VERIFIER_nondet_int();
  m3 = __VERIFIER_nondet_int();
  s  = __VERIFIER_nondet_int();
  t  = __VERIFIER_nondet_int();
  x  = __VERIFIER_nondet_int();
  b  = __VERIFIER_nondet_bool();

  // main method
  assume_abort_if_not( s == t && s == x && s == 0 && b == 0 );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not(b);
  reach_error();

  return 0;
}