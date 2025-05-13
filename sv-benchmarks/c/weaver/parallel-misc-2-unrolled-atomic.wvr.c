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
void reach_error() { __assert_fail("0", "parallel-misc-2-unrolled-atomic.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int   __VERIFIER_nondet_int(void);
extern void  __VERIFIER_atomic_begin();
extern void  __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int pos, i1, i2, N;

void* thread1(void* _argptr) {
  while (( i1 < ( 2 * N ) )) {
    __VERIFIER_atomic_begin();
    pos++;
    i1++;
    pos--;
    i1++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  while (( i2 < ( 2 * N ) )) {
    __VERIFIER_atomic_begin();
    pos = ( pos + 2 );
    i2++;
    pos = ( pos - 2 );
    i2++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2;

  // initialize global variables
  pos = __VERIFIER_nondet_int();
  i1  = __VERIFIER_nondet_int();
  i2  = __VERIFIER_nondet_int();
  N   = __VERIFIER_nondet_int();

  // main method
  assume_abort_if_not( pos == i1 && pos == i2 && pos == 0 );
  assume_abort_if_not(N >= 0 && N <= 2147483647 / 2);

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( pos != 0 );
  reach_error();

  return 0;
}