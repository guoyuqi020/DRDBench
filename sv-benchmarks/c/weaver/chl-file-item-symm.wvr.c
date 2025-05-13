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
void reach_error() { __assert_fail("0", "chl-file-item-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int  __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int filename_1, filename_4, result_6, result_7;
_Bool isNull_0, isNull_3, filename_2, filename_5;

int minus(int a, int b);

void* thread1(void* _argptr) {
  result_6 = isNull_0 ? (isNull_3 ? 0 : 1) : (isNull_3 ? -1 : (filename_2 ? (filename_5 ? 0 : 1) : (filename_5 ? -1 : minus(filename_1, filename_4))));

  return 0;
}

void* thread2(void* _argptr) {
  result_7 = isNull_3 ? (isNull_0 ? 0 : 1) : (isNull_0 ? -1 : (filename_5 ? (filename_2 ? 0 : 1) : (filename_2 ? -1 : minus(filename_4, filename_1))));

  return 0;
}

int main() {
  pthread_t t1, t2;
  
  filename_1 = __VERIFIER_nondet_int();
  filename_4 = __VERIFIER_nondet_int();
  isNull_0 = __VERIFIER_nondet_bool();
  isNull_3 = __VERIFIER_nondet_bool();
  filename_2 = __VERIFIER_nondet_bool();
  filename_5 = __VERIFIER_nondet_bool();
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not(!(result_6 < 0 && result_7 > 0));
  assume_abort_if_not(!(result_6 > 0 && result_7 < 0));
  assume_abort_if_not(!(result_6 == 0 && result_7 == 0));
  reach_error();

  return 0;
}

int minus(int a, int b) {
  assume_abort_if_not(b <= 0 || a >= b - 2147483648);
  assume_abort_if_not(b >= 0 || a <= b + 2147483647);
  return a - b;
}