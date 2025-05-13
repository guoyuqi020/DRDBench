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
void reach_error() { __assert_fail("0", "chl-chromosome-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int  __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int *o_0, *o_2;
int result_5, result_8;
_Bool isNull_1, isNull_3;

int *create_fresh_int_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  assume_abort_if_not(!isNull_1);
  _Bool stop = isNull_3;
  result_5 = 1;
  int i = 0;
  while (!stop && i<5) {
    result_5 = minus(o_0[i], o_2[i]);
    stop = (result_5 != 0);
    i++;
  }
  result_5 = stop ? result_5 : 0;
  return 0;
}

void* thread2(void* _argptr) {
  assume_abort_if_not(!isNull_3);
  _Bool stop = isNull_1;
  result_8 = 1;
  int i = 0;
  while (!stop && i<5) {
    result_8 = minus(o_2[i], o_0[i]);
    stop = (result_8 != 0);
    i++;
  }
  result_8 = stop ? result_8 : 0;
  return 0;
}

int main() {
  pthread_t t1, t2;
  
  o_0 = create_fresh_int_array(5);
  o_2 = create_fresh_int_array(5);
  isNull_1 = __VERIFIER_nondet_bool();
  isNull_3 = __VERIFIER_nondet_bool();
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not(!(result_5 < 0 && result_8 > 0));
  assume_abort_if_not(!(result_5 > 0 && result_8 < 0));
  assume_abort_if_not(!(result_5 == 0 && result_8 == 0));
  reach_error();

  return 0;
}

int *create_fresh_int_array(int size) {
  assume_abort_if_not(size >= 0);
  assume_abort_if_not(size <= (((size_t) 4294967295) / sizeof(int)));

  int* arr = (int*)malloc(sizeof(int) * (size_t)size);
  for (int i = 0; i < size; i++) {
    arr[i] = __VERIFIER_nondet_int();
  }
  return arr;
}

int minus(int a, int b) {
  assume_abort_if_not(b <= 0 || a >= b - 2147483648);
  assume_abort_if_not(b >= 0 || a <= b + 2147483647);
  return a - b;
}