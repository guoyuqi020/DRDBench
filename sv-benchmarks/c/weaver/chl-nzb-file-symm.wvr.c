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
void reach_error() { __assert_fail("0", "chl-nzb-file-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int filename_0, get_subject_3, filename_4, get_subject_7, result_8, i_9, result_11, i_12;
_Bool is_null_1, is_null_5, break_10, break_13;
_Bool *ends_with_2, *ends_with_6;

_Bool *create_fresh_bool_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  if ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( !is_null_1 && !is_null_5 );
    i_9 = 0;
    break_10 = 0;
 
    while ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( ( i_9 < 5 ) && !break_10 );
      result_8 = ( ( ends_with_2[i_9] && ends_with_6[i_9] ) ? 0 : result_8 );
      break_10 = ( ( ends_with_2[i_9] && ends_with_6[i_9] ) ? 1 : break_10 );
      result_8 = ( ( !break_10 && ends_with_2[i_9] ) ? ( ( 0 - 1000 ) + i_9 ) : result_8 );
      break_10 = ( ( !break_10 && ends_with_2[i_9] ) ? 1 : break_10 );
      result_8 = ( ( !break_10 && ends_with_6[i_9] ) ? ( 1000 + i_9 ) : result_8 );
      break_10 = ( ( !break_10 && ends_with_6[i_9] ) ? 1 : break_10 );
      i_9++;
    }
    assume_abort_if_not( !( ( i_9 < 5 ) && !break_10 ) );
    result_8 = ( (!break_10) ? minus(filename_0, filename_4) : result_8 );
  }
  else {
    assume_abort_if_not( !( !is_null_1 && !is_null_5 ) );
    result_8 = ( ( !is_null_1 && is_null_5 ) ? ( 0 - 995 ) : ( ( is_null_1 && !is_null_5 ) ? 1005 : minus(get_subject_3, get_subject_7) ) );
  }

  return 0;
}

void* thread2(void* _argptr) {
  if ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( !is_null_5 && !is_null_1 );
    i_12 = 0;
    break_13 = 0;

    while ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( ( i_12 < 5 ) && !break_13 );
      result_11 = ( ( ends_with_6[i_12] && ends_with_2[i_12] ) ? 0 : result_11 );
      break_13  = ( ( ends_with_6[i_12] && ends_with_2[i_12] ) ? 1 : break_13 );
      result_11 = ( ( !break_13 && ends_with_6[i_12] ) ? ( ( 0 - 1000 ) + i_12 ) : result_11 );
      break_13  = ( ( !break_13 && ends_with_6[i_12] ) ? 1 : break_13 );
      result_11 = ( ( !break_13 && ends_with_2[i_12] ) ? ( 1000 + i_12 ) : result_11 );
      break_13  = ( ( !break_13 && ends_with_2[i_12] ) ? 1 : break_13 );
      i_12++;
    }
    assume_abort_if_not( !( ( i_12 < 5 ) && !break_13 ) );
    result_11 = ( (!break_13) ? minus(filename_4, filename_0) : result_11 );
  }
  else {
    assume_abort_if_not( !( !is_null_5 && !is_null_1 ) );
    result_11 = ( ( !is_null_5 && is_null_1 ) ? ( 0 - 995 ) : ( ( is_null_5 && !is_null_1 ) ? 1005 : minus(get_subject_7, get_subject_3) ) );
  }

  return 0;
}

int main() {
  pthread_t t1, t2;

  // initialize global variables
  filename_0 = __VERIFIER_nondet_int();
  get_subject_3 = __VERIFIER_nondet_int();
  filename_4 = __VERIFIER_nondet_int();
  get_subject_7 = __VERIFIER_nondet_int();
  result_8 = __VERIFIER_nondet_int();
  i_9 = __VERIFIER_nondet_int();
  result_11 = __VERIFIER_nondet_int();
  i_12 = __VERIFIER_nondet_int();
  is_null_1 = __VERIFIER_nondet_bool();
  is_null_5 = __VERIFIER_nondet_bool();
  break_10 = __VERIFIER_nondet_bool();
  break_13 = __VERIFIER_nondet_bool();
  ends_with_2  = create_fresh_bool_array(5);
  ends_with_6  = create_fresh_bool_array(5);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( !( ( ( result_8 < 0 ) ? ( - 1 ) : ( ( result_8 > 0 ) ? 1 : 0 ) ) == ( 0 - ( ( result_11 < 0 ) ? ( - 1 ) : ( ( result_11 > 0 ) ? 1 : 0 ) ) ) ) );
  reach_error();

  return 0;
}

_Bool *create_fresh_bool_array(int size) {
  assume_abort_if_not(size >= 0);
  assume_abort_if_not(size <= (((size_t) 4294967295) / sizeof(_Bool)));

  _Bool* arr = (_Bool*)malloc(sizeof(_Bool) * (size_t)size);
  for (int i = 0; i < size; i++) {
    arr[i] = __VERIFIER_nondet_bool();
  }
  return arr;
}

int minus(int a, int b) {
  assume_abort_if_not(b <= 0 || a >= b - 2147483648);
  assume_abort_if_not(b >= 0 || a <= b + 2147483647);
  return a - b;
}