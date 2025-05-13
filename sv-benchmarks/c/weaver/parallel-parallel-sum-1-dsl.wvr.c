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
void reach_error() { __assert_fail("0", "parallel-parallel-sum-1-dsl.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int* X_0;
int n_1, s_2, i_3, t_4, t_5, s_6, i_7, t_8, t_9;

int *create_fresh_int_array(int size);
int plus(int a, int b);

void* thread2(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i_3 < n_1 );
    i_3++;
    t_4 = X_0[i_3];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s_2 = plus(s_2, t_4);
    __VERIFIER_atomic_end();
  }
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( i_3 < n_1 ) );
  __VERIFIER_atomic_end();

  return 0;
}

void* thread3(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i_3 < n_1 );
    i_3++;
    t_5 = X_0[i_3];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s_2 = plus(s_2, t_5);
    __VERIFIER_atomic_end();
  }
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( i_3 < n_1 ) );
  __VERIFIER_atomic_end();

  return 0;
}

void* thread1(void* _argptr) {
  pthread_t t2, t3;

  __VERIFIER_atomic_begin();
  i_3 = 0;
  s_2 = 0;
  __VERIFIER_atomic_end();

  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  return 0;
}

void* thread5(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i_7 < n_1 );
    i_7++;
    t_8 = X_0[i_7];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s_6 = plus(s_6, t_8);
    __VERIFIER_atomic_end();
  }
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( i_7 < n_1 ) );
  __VERIFIER_atomic_end();

  return 0;
}

void* thread6(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not( i_7 < n_1 );
    i_7++;
    t_9 = X_0[i_7];
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    s_6 = plus(s_6, t_9);
    __VERIFIER_atomic_end();
  }
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( i_7 < n_1 ) );
  __VERIFIER_atomic_end();

  return 0;
}

void* thread4(void* _argptr) {
  pthread_t t5, t6;

  __VERIFIER_atomic_begin();
  i_7 = 0;
  s_6 = 0;
  __VERIFIER_atomic_end();

  pthread_create(&t5, 0, thread5, 0);
  pthread_create(&t6, 0, thread6, 0);
  pthread_join(t5, 0);
  pthread_join(t6, 0);

  return 0;
}

int main() {
  pthread_t t1, t4;

  // initialize global variables
  n_1 = __VERIFIER_nondet_int();
  s_2 = __VERIFIER_nondet_int();
  i_3 = __VERIFIER_nondet_int();
  t_4 = __VERIFIER_nondet_int();
  t_5 = __VERIFIER_nondet_int();
  s_6 = __VERIFIER_nondet_int();
  i_7 = __VERIFIER_nondet_int();
  t_8 = __VERIFIER_nondet_int();
  t_9 = __VERIFIER_nondet_int();
  assume_abort_if_not(n_1 < 2147483647);
  X_0 = create_fresh_int_array(n_1 + 1);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t4, 0);

  assume_abort_if_not( !( s_2 == s_6 ) );
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