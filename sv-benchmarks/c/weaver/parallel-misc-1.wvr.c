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
void reach_error() { __assert_fail("0", "parallel-misc-1.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int   __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int* A;
int bag1, bag2, cap1, cap2, sum1, sum2, i, j, N;

int *create_fresh_int_array(int size);
int plus(int a, int b);

void* thread1(void* _argptr) {
  while (( i < N )) {
    if (plus(bag1, A[i]) < cap1) {
      bag1 = plus(bag1, A[i]);

    }
    else {
      sum1 = plus(sum1, bag1);
      bag1 = A[i];

    }
    i++;
  }
  sum1 = plus(sum1, bag1);
  return 0;
}

void* thread2(void* _argptr) {
  while (( j < N )) {
    if (plus(bag2, A[j]) < cap2) {
      bag2 = plus(bag2, A[j]);

    }
    else {
      sum2 = plus(sum2, bag2);
      bag2 = A[j];

    }
    j++;
  }
  sum2 = plus(sum2, bag2);
  return 0;
}

int main() {
  pthread_t t1, t2;

  // initialize global variables
  bag1 = __VERIFIER_nondet_int();
  bag2 = __VERIFIER_nondet_int();
  cap1 = __VERIFIER_nondet_int();
  cap2 = __VERIFIER_nondet_int();
  sum1 = __VERIFIER_nondet_int();
  sum2 = __VERIFIER_nondet_int();
  i    = __VERIFIER_nondet_int();
  j    = __VERIFIER_nondet_int();
  N    = __VERIFIER_nondet_int();
  A    = create_fresh_int_array(N);

  // main method
  assume_abort_if_not( bag1 == bag2 && bag1 == sum1 && bag1 == sum2 && bag1 == i && bag1 == j && bag1 == 0 );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( sum1 != sum2 );
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

int plus(int a, int b) {
  assume_abort_if_not(b >= 0 || a >= -2147483648 - b);
  assume_abort_if_not(b <= 0 || a <= 2147483647 - b);
  return a + b;
}