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
void reach_error() { __assert_fail("0", "chl-name-comparator-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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
int name_1, name_2, result_3, i_4, current_5, break_6, result_7, i_8, current_9, break_10;

int *create_fresh_int_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  i_4 = 0;
  break_6 = 0;
  result_3 = ( name_1 == name_2 ) ? 0 : result_3;
  break_6 = ( name_1 == name_2 ) ? 1 : break_6;

  while ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( ( i_4 < 3 ) && !break_6 );
    current_5 = nondet_0[i_4];
    result_3 = ( current_5 == name_1 ) ? 1 : result_3;
    break_6  = ( current_5 == name_1 ) ? 1 : break_6;
    result_3 = ( !break_6 && ( current_5 == name_2 ) ) ? ( 0 - 1 ) : result_3;
    break_6  = ( !break_6 && ( current_5 == name_2 ) ) ? 1 : break_6;
    i_4++;
  }
  assume_abort_if_not( !( ( i_4 < 3 ) && !break_6 ) );
  result_3 = ( !break_6 ) ? minus(name_1, name_2) : result_3;

  return 0;
}

void* thread2(void* _argptr) {
  i_8 = 0;
  break_10 = 0;
  result_7 = ( name_2 == name_1 ) ? 0 : result_7;
  break_10 = ( name_2 == name_1 ) ? 1 : break_10;

  while ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( ( i_8 < 3 ) && !break_10 );
    current_9 = nondet_0[i_8];
    result_7 = ( current_9 == name_2 ) ? 1 : result_7;
    break_10 = ( current_9 == name_2 ) ? 1 : break_10;
    result_7 = ( !break_10 && ( current_9 == name_1 ) ) ? ( 0 - 1 ) : result_7;
    break_10 = ( !break_10 && ( current_9 == name_1 ) ) ? 1 : break_10;
    i_8++;
  }

  assume_abort_if_not( !( ( i_8 < 3 ) && !break_10 ) );
  result_7 = (!break_10) ? minus(name_2, name_1) : result_7;

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  // initialize global variables
  name_1 = __VERIFIER_nondet_int();
  name_2 = __VERIFIER_nondet_int();
  result_3 = __VERIFIER_nondet_int();
  i_4 = __VERIFIER_nondet_int();
  current_5 = __VERIFIER_nondet_int();
  break_6 = __VERIFIER_nondet_int();
  result_7 = __VERIFIER_nondet_int();
  i_8 = __VERIFIER_nondet_int();
  current_9 = __VERIFIER_nondet_int();
  break_10 = __VERIFIER_nondet_int();
  nondet_0 = create_fresh_int_array(3);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( !( ( ( result_3 < 0 ) ? ( - 1 ) : ( ( result_3 > 0 ) ? 1 : 0 ) ) == ( 0 - ( ( result_7 < 0 ) ? ( - 1 ) : ( ( result_7 > 0 ) ? 1 : 0 ) ) ) ) );
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
