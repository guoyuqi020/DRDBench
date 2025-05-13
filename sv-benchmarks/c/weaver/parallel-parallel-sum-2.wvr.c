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
void reach_error() { __assert_fail("0", "parallel-parallel-sum-2.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int   __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void  __VERIFIER_atomic_begin();
extern void  __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int* x;
int i1, i2, t11, t21, t12, t22, s11, s21, s12, s22, x1, x2, n;

int *create_fresh_int_array(int size);
int plus(int a, int b);

void* thread2(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i1 < n );
    i1++;
    t11 = x[i1];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s11 = plus(s11, t11);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i1 < n );
    i1++;
    t21 = x[i1];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s21 = plus(s21, t21);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread1(void* _argptr) {
  pthread_t t2, t3;

  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not( i1 == n );
  __VERIFIER_atomic_begin();
  x1 = plus(s11, s21);
  __VERIFIER_atomic_end();

  return 0;
}

void* thread5(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i2 < n );
    i2++;
    t12 = x[i2];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s12 = plus(s12, t12);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread6(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i2 < n );
    i2++;
    t22 = x[i2];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s22 = plus(s22, t22);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread4(void* _argptr) {
  pthread_t t5, t6;

  pthread_create(&t5, 0, thread5, 0);
  pthread_create(&t6, 0, thread6, 0);
  pthread_join(t5, 0);
  pthread_join(t6, 0);

  assume_abort_if_not ( i2 == n );
  __VERIFIER_atomic_begin();
  x2 = plus(s12, s22);
  __VERIFIER_atomic_end();

  return 0;
}

int main() {
  pthread_t t1, t4;

  // initialize global variables
  i1  = __VERIFIER_nondet_int();
  i2  = __VERIFIER_nondet_int();
  t11 = __VERIFIER_nondet_int();
  t21 = __VERIFIER_nondet_int();
  t12 = __VERIFIER_nondet_int();
  t22 = __VERIFIER_nondet_int();
  s11 = __VERIFIER_nondet_int();
  s21 = __VERIFIER_nondet_int();
  s22 = __VERIFIER_nondet_int();
  x1  = __VERIFIER_nondet_int();
  x2  = __VERIFIER_nondet_int();
  n   = __VERIFIER_nondet_int();
  assume_abort_if_not(n < 2147483647);
  x = create_fresh_int_array(n + 1);
  assume_abort_if_not(s11 == s21 && s11 == s12 && s11 == s22 && s11 == i1 && s11 == i2 && s11 == 0);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t4, 0);

  assume_abort_if_not( !(x1 == x2) );
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