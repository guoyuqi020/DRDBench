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
void reach_error() { __assert_fail("0", "chl-name-comparator-trans.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int* nondet_0;
int name_1, name_2, name_3, result_4, i_5, current_6, break_7, result_8, i_9, current_10, break_11, result_12, i_13, current_14, break_15;

int *create_fresh_int_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  i_5 = 0;
  break_7 = 0;
  result_4 = ( name_1 == name_2 ) ? 0 : result_4;
  break_7 = ( name_1 == name_2 ) ? 1 : break_7;

  while ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( ( i_5 < 3 ) && !break_7 );
    current_6 = nondet_0[i_5];
    result_4 = ( current_6 == name_1 ) ? 1 : result_4;
    break_7  = ( current_6 == name_1 ) ? 1 : break_7;
    result_4 = ( !break_7 && ( current_6 == name_2 ) ) ? ( 0 - 1 ) : result_4;
    break_7  = ( !break_7 && ( current_6 == name_2 ) ) ? 1 : break_7;
    i_5++;
  }
  assume_abort_if_not( !( ( i_5 < 3 ) && !break_7 ) );
  result_4 = ( !break_7 ) ? minus(name_1, name_2) : result_4;

  return 0;
}

void* thread2(void* _argptr) {
  i_9 = 0;
  break_11 = 0;
  result_8 = ( name_2 == name_3 ) ? 0 : result_8;
  break_11 = ( name_2 == name_3 ) ? 1 : break_11;

  while ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( ( i_9 < 3 ) && !break_11 );
    current_10 = nondet_0[i_9];
    result_8 = ( current_10 == name_2 ) ? 1 : result_8;
    break_11 = ( current_10 == name_2 ) ? 1 : break_11;
    result_8 = ( !break_11 && ( current_10 == name_3 ) ) ? ( 0 - 1 ) : result_8;
    break_11 = ( !break_11 && ( current_10 == name_3 ) ) ? 1 : break_11;
    i_9++;
  }

  assume_abort_if_not( !( ( i_9 < 3 ) && !break_11 ) );
  result_8 = (!break_11) ? minus(name_2, name_3) : result_8;

  return 0;
}

void* thread3(void* _argptr) {
  i_13 = 0;
  break_15 = 0;
  result_12 = ( name_1 == name_3 ) ? 0 : result_12;
  break_15  = ( name_1 == name_3 ) ? 1 : break_15;

  while ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( ( i_13 < 3 ) && !break_15 );
    current_14 = nondet_0[i_13];
    result_12 = ( current_14 == name_1 ) ? 1 : result_12;
    break_15  = ( current_14 == name_1 ) ? 1 : break_15;
    result_12 = ( !break_15 && ( current_14 == name_3 ) ) ? ( 0 - 1 ) : result_12;
    break_15  = ( !break_15 && ( current_14 == name_3 ) ) ? 1 : break_15;
    i_13++;
  }

  assume_abort_if_not( !( ( i_13 < 3 ) && !break_15 ) );
  result_12 = (!break_15) ? minus(name_1, name_3) : result_12;

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  // initialize global variables
  name_1 = __VERIFIER_nondet_int();
  name_2 = __VERIFIER_nondet_int();
  name_3 = __VERIFIER_nondet_int();
  result_4 = __VERIFIER_nondet_int();
  i_5 = __VERIFIER_nondet_int();
  current_6 = __VERIFIER_nondet_int();
  break_7 = __VERIFIER_nondet_int();
  result_8 = __VERIFIER_nondet_int();
  i_9 = __VERIFIER_nondet_int();
  current_10 = __VERIFIER_nondet_int();
  break_11 = __VERIFIER_nondet_int();
  result_12 = __VERIFIER_nondet_int();
  i_13 = __VERIFIER_nondet_int();
  current_14 = __VERIFIER_nondet_int();
  break_15 = __VERIFIER_nondet_int();
  nondet_0 = create_fresh_int_array(3);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not( !( !( ( result_4 > 0 ) && ( result_8 > 0 ) ) || ( result_12 > 0 ) ) );
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