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
void reach_error() { __assert_fail("0", "clever.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int __VERIFIER_nondet_int();
extern unsigned int __VERIFIER_nondet_uint();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int n, m, i1, i2, j1;
unsigned int k1, k2;

void* thread1(void* _argptr) {
  while (i1 < n) {
    for (j1 = 0; j1 < m; j1++) {
      k1++;
    }
    i1++;
  }

  return 0;
}

void* thread2(void* _argptr) {
  while (i2 < n) {
    k2 = k2 + m;
    i2++;
  }

  return 0;
}

int main() {
  pthread_t t1, t2;

  // initialize global variables
  n  = __VERIFIER_nondet_int();
  m  = __VERIFIER_nondet_int();
  i1 = __VERIFIER_nondet_int();
  i2 = __VERIFIER_nondet_int();
  j1 = __VERIFIER_nondet_int();
  k1 = __VERIFIER_nondet_uint();
  k2 = __VERIFIER_nondet_uint();

  // main method
  assume_abort_if_not( i1 == i2 && i1 == k1 && i1 == k2 && i1 == 0 );
  assume_abort_if_not( m >= 0 );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( !(k1 == k2) );
  reach_error();

  return 0;
}
