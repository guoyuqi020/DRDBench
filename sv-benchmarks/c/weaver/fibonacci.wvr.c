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
void reach_error() { __assert_fail("0", "fibonacci.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin();
extern void __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int n_0, f1_2, f2_3, l_4, f1_6, f2_7, l_8;

int minus(int a, int b);
int plus(int a, int b);

void* thread1(void* _argptr) {
  for (int i=0; i<n_0; i++) {
    f1_2 = plus(f1_2, f2_3);
    f2_3 = minus(f1_2, f2_3);
  }
  l_4 = (f1_2 > 0) ? 1 : 0;

  return 0;
}

void* thread2(void* _argptr) {
  for (int i=0; i<n_0; i++) {
    f1_6 = plus(f1_6, f2_7);
    f2_7 = minus(f1_6, f2_7);
  }
  l_8 = (f1_6 > 0) ? 1 : 0;

  return 0;
}

int main() {
  pthread_t t1, t2;

  // initialize global variables
  n_0  = __VERIFIER_nondet_int();
  f1_2 = __VERIFIER_nondet_int();
  f2_3 = __VERIFIER_nondet_int();
  l_4  = __VERIFIER_nondet_int();
  f1_6 = __VERIFIER_nondet_int();
  f2_7 = __VERIFIER_nondet_int();
  l_8  = __VERIFIER_nondet_int();

  // main method
  assume_abort_if_not(f1_2 == f1_6 && f2_3 == f2_7);

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not(l_4 != l_8);
  reach_error();

  return 0;
}

int minus(int a, int b) {
  assume_abort_if_not(b <= 0 || a >= b - 2147483648);
  assume_abort_if_not(b >= 0 || a <= b + 2147483647);
  return a - b;
}

int plus(int a, int b) {
  assume_abort_if_not(b >= 0 || a >= -2147483648 - b);
  assume_abort_if_not(b <= 0 || a <= 2147483647 - b);
  return a + b;
}
