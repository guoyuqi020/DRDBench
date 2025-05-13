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
void reach_error() { __assert_fail("0", "chl-file-item-subst.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int filename_1, filename_4, filename_7, result_9, result_10, result_11;
_Bool is_null_0, is_null_3, is_null_6, filename_is_null_2, filename_is_null_5, filename_is_null_8;

int minus(int a, int b);

void* thread1(void* _argptr) {
  result_9 = is_null_0 ? (is_null_3 ? 0 : 1) : (is_null_3 ? -1 : (filename_is_null_2 ? (filename_is_null_5 ? 0 : 1) : (filename_is_null_5 ? -1 : minus(filename_1, filename_4))));

  return 0;
}

void* thread2(void* _argptr) {
  result_10 = is_null_0 ? (is_null_6 ? 0 : 1) : (is_null_6 ? -1 : (filename_is_null_2 ? (filename_is_null_8 ? 0 : 1) : (filename_is_null_8 ? -1 : minus(filename_1, filename_7))));

  return 0;
}

void* thread3(void* _argptr) {
  result_11 = is_null_3 ? (is_null_6 ? 0 : 1) : (is_null_6 ? -1 : (filename_is_null_5 ? (filename_is_null_8 ? 0 : 1) : (filename_is_null_8 ? -1 : minus(filename_4, filename_7))));

  return 0;
}

int main() {
  pthread_t t1, t2, t3;
  
  filename_1 = __VERIFIER_nondet_int();
  filename_4 = __VERIFIER_nondet_int();
  filename_7 = __VERIFIER_nondet_int();
  is_null_0 = __VERIFIER_nondet_bool();
  is_null_3 = __VERIFIER_nondet_bool();
  is_null_6 = __VERIFIER_nondet_bool();
  filename_is_null_2 = __VERIFIER_nondet_bool();
  filename_is_null_5 = __VERIFIER_nondet_bool();
  filename_is_null_8 = __VERIFIER_nondet_bool();
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not(result_9 == 0);
  assume_abort_if_not((result_10 > 0) != (result_11 > 0) || (result_10 < 0) != (result_11 < 0));
  reach_error();

  return 0;
}

int minus(int a, int b) {
  assume_abort_if_not(b <= 0 || a >= b - 2147483648);
  assume_abort_if_not(b >= 0 || a <= b + 2147483647);
  return a - b;
}