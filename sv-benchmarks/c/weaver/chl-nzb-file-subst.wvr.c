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
void reach_error() { __assert_fail("0", "chl-nzb-file-subst.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int filename_0, get_subject_3, filename_4, get_subject_7, filename_8, get_subject_11, result_12, i_13, result_15, i_16, result_18, i_19;
_Bool is_null_1, is_null_5, is_null_9, break_14, break_17, break_20;
_Bool *ends_with_2, *ends_with_6, *ends_with_10;

_Bool *create_fresh_bool_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  if ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( !is_null_1 && !is_null_5 );
    i_13 = 0;
    break_14 = 0;
 
    while ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( ( i_13 < 5 ) && !break_14 );
      result_12 = ( ( ends_with_2[i_13] && ends_with_6[i_13] ) ? 0 : result_12 );
      break_14  = ( ( ends_with_2[i_13] && ends_with_6[i_13] ) ? 1 : break_14 );
      result_12 = ( ( !break_14 && ends_with_2[i_13] ) ? ( ( 0 - 1000 ) + i_13 ) : result_12 );
      break_14  = ( ( !break_14 && ends_with_2[i_13] ) ? 1 : break_14 );
      result_12 = ( ( !break_14 && ends_with_6[i_13] ) ? ( 1000 + i_13 ) : result_12 );
      break_14  = ( ( !break_14 && ends_with_6[i_13] ) ? 1 : break_14 );
      i_13++;
    }
    assume_abort_if_not( !( ( i_13 < 5 ) && !break_14 ) );
    result_12 = ( (!break_14) ? minus(filename_0, filename_4) : result_12 );
  }
  else {
    assume_abort_if_not( !( !is_null_1 && !is_null_5 ) );
    result_12 = ( ( !is_null_1 && is_null_5 ) ? ( 0 - 995 ) : ( ( is_null_1 && !is_null_5 ) ? 1005 : minus(get_subject_3, get_subject_7) ) );
  }

  return 0;
}

void* thread2(void* _argptr) {
  if ( __VERIFIER_nondet_bool() ) {
    assume_abort_if_not( !is_null_1 && !is_null_9 );
    i_16 = 0;
    break_17 = 0;

    while ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( ( i_16 < 5 ) && !break_17 );
      result_15 = ( ( ends_with_2[i_16] && ends_with_10[i_16] ) ? 0 : result_15 );
      break_17  = ( ( ends_with_2[i_16] && ends_with_10[i_16] ) ? 1 : break_17 );
      result_15 = ( ( !break_17 && ends_with_2[i_16] ) ? ( ( 0 - 1000 ) + i_16 ) : result_15 );
      break_17  = ( ( !break_17 && ends_with_2[i_16] ) ? 1 : break_17 );
      result_15 = ( ( !break_17 && ends_with_10[i_16] ) ? ( 1000 + i_16 ) : result_15 );
      break_17  = ( ( !break_17 && ends_with_10[i_16] ) ? 1 : break_17 );
      i_16++;
    }
    assume_abort_if_not( !( ( i_16 < 5 ) && !break_17 ) );
    result_15 = ( (!break_17) ? minus(filename_0, filename_8) : result_15 );
  }
  else {
    assume_abort_if_not( !( !is_null_1 && !is_null_9 ) );
    result_15 = ( ( !is_null_1 && is_null_9 ) ? ( 0 - 995 ) : ( ( is_null_1 && !is_null_9 ) ? 1005 : minus(get_subject_3, get_subject_11) ) );
  }

  return 0;
}

void* thread3(void* _argptr) {
  if ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( !is_null_5 && !is_null_9 );
      i_19 = 0;
      break_20 = 0;

    while ( __VERIFIER_nondet_bool() ) {
      assume_abort_if_not( ( i_19 < 5 ) && !break_20 );
      result_18 = ( ( ends_with_6[i_19] && ends_with_10[i_19] ) ? 0 : result_18 );
      break_20  = ( ( ends_with_6[i_19] && ends_with_10[i_19] ) ? 1 : break_20 );
      result_18 = ( ( !break_20 && ends_with_6[i_19] ) ? ( ( 0 - 1000 ) + i_19 ) : result_18 );
      break_20  = ( ( !break_20 && ends_with_6[i_19] ) ? 1 : break_20 );
      result_18 = ( ( !break_20 && ends_with_10[i_19] ) ? ( 1000 + i_19 ) : result_18 );
      break_20  = ( ( !break_20 && ends_with_10[i_19] ) ? 1 : break_20 );
      i_19++;
    }
    assume_abort_if_not( !( ( i_19 < 5 ) && !break_20 ) );
    result_18 = ( (!break_20) ? minus(filename_4, filename_8) : result_18 );
  }
  else {
    assume_abort_if_not( !( !is_null_5 && !is_null_9 ) );
    result_18 = ( ( !is_null_5 && is_null_9 ) ? ( 0 - 995 ) : ( ( is_null_5 && !is_null_9 ) ? 1005 : minus(get_subject_7, get_subject_11) ) );
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  // initialize global variables
  filename_0 = __VERIFIER_nondet_int();
  get_subject_3 = __VERIFIER_nondet_int();
  filename_4 = __VERIFIER_nondet_int();
  get_subject_7 = __VERIFIER_nondet_int();
  filename_8 = __VERIFIER_nondet_int();
  get_subject_11 = __VERIFIER_nondet_int();
  result_12 = __VERIFIER_nondet_int();
  i_13 = __VERIFIER_nondet_int();
  result_15 = __VERIFIER_nondet_int();
  i_16 = __VERIFIER_nondet_int();
  result_18 = __VERIFIER_nondet_int();
  i_19 = __VERIFIER_nondet_int();
  is_null_1 = __VERIFIER_nondet_bool();
  is_null_5 = __VERIFIER_nondet_bool();
  is_null_9 = __VERIFIER_nondet_bool();
  break_14 = __VERIFIER_nondet_bool();
  break_17 = __VERIFIER_nondet_bool();
  break_20 = __VERIFIER_nondet_bool();
  ends_with_2  = create_fresh_bool_array(5);
  ends_with_6  = create_fresh_bool_array(5);
  ends_with_10 = create_fresh_bool_array(5);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not( !( !( result_12 == 0 ) || ( ( ( result_15 > 0 ) == ( result_18 > 0 ) ) && ( ( result_15 < 0 ) == ( result_18 < 0 ) ) ) ) );
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