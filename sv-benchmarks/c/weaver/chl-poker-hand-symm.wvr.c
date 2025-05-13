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
void reach_error() { __assert_fail("0", "chl-poker-hand-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int *index_of_0, *char_at_1, *count_occurrences_of_2, *last_index_of_3, *index_of_4, *char_at_5, *count_occurrences_of_6, *last_index_of_7;
int result_8, i1_9, i2_11, result_13, i1_14, i2_16;
_Bool break_10, break_12, break_15, break_17;

int *create_fresh_int_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not ( ( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ) && ( index_of_0[4] == index_of_4[4] ) );
    i1_9 = 0;
    break_10 = 0;
    __VERIFIER_atomic_end();
    while (__VERIFIER_nondet_bool()) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not ( !break_10 && ( i1_9 <= 12 ) );
      result_8 = ( ( ( char_at_1[i1_9] != 0 ) && ( ( char_at_1[i1_9] != 4 ) && ( ( char_at_5[i1_9] != 0 ) && ( char_at_5[i1_9] != 4 ) ) ) ) ? 0 : ( ( ( char_at_1[i1_9] != 0 ) && ( char_at_1[i1_9] != 4 ) ) ? ( 0 - 1 ) : ( ( ( char_at_5[i1_9] != 0 ) && ( char_at_5[i1_9] != 4 ) ) ? 1 : result_8 ) ) );
      break_10 = ( ( ( ( char_at_1[i1_9] != 0 ) && ( char_at_1[i1_9] != 4 ) ) || ( ( char_at_5[i1_9] != 0 ) && ( char_at_5[i1_9] != 4 ) ) ) ? 1 : break_10 );
      i1_9 = ( i1_9 + 1 );
      __VERIFIER_atomic_end();
    }
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( !break_10 && ( i1_9 <= 12 ) ));
    result_8 = ( !break_10 ? minus(index_of_0[4], index_of_4[4]) : result_8 );
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not ( ( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ) && !( index_of_0[4] == index_of_4[4] ) );
    result_8 = minus(index_of_0[4], index_of_4[4]);
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( last_index_of_3[3] == last_index_of_7[3] );
    i2_11 = 0;
    break_12 = 0;
    __VERIFIER_atomic_end();
    while (__VERIFIER_nondet_bool()) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not ( !break_12 && ( i2_11 <= 12 ) );
      result_8 = ( ( ( i2_11 != last_index_of_3[3] ) && ( ( ( char_at_1[i2_11] == 2 ) || ( char_at_1[i2_11] == 3 ) ) && ( ( char_at_5[i2_11] == 2 ) || ( char_at_5[i2_11] == 3 ) ) ) ) ? 0 : ( ( ( i2_11 != last_index_of_3[3] ) && ( ( char_at_1[i2_11] == 2 ) || ( char_at_1[i2_11] == 3 ) ) ) ? ( 0 - 1 ) : ( ( ( i2_11 != last_index_of_3[3] ) && ( ( char_at_5[i2_11] == 2 ) || ( char_at_5[i2_11] == 3 ) ) ) ? 1 : result_8 ) ) );
      break_12 = ( ( ( i2_11 != last_index_of_3[3] ) && ( ( char_at_1[i2_11] == 2 ) || ( ( char_at_1[i2_11] == 3 ) || ( ( char_at_5[i2_11] == 2 ) || ( char_at_5[i2_11] == 3 ) ) ) ) ) ? 1 : break_12 );
      __VERIFIER_atomic_end();
    }
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( !break_12 && ( i2_11 <= 12 ) ));
    result_8 = ( !break_12 ? minus(last_index_of_3[3], last_index_of_7[3]) : result_8 );
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not(!( last_index_of_3[3] == last_index_of_7[3] ));
    result_8 = minus(last_index_of_3[3], last_index_of_7[3]);
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not(!( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) ));
    result_8 = 1;
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    result_8 = ( 0 - 1 );
    __VERIFIER_atomic_end();
  }
  else {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_0[4] != ( 0 - 1 ) ) || ( index_of_4[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) ));
    result_8 = 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not ( ( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ) && ( index_of_4[4] == index_of_0[4] ) );
    i1_14 = 0;
    break_15 = 0;
    __VERIFIER_atomic_end();
    while (__VERIFIER_nondet_bool()) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not ( !break_15 && ( i1_14 <= 12 ) );
      result_13 = ( ( ( char_at_5[i1_14] != 0 ) && ( ( char_at_5[i1_14] != 4 ) && ( ( char_at_1[i1_14] != 0 ) && ( char_at_1[i1_14] != 4 ) ) ) ) ? 0 : ( ( ( char_at_5[i1_14] != 0 ) && ( char_at_5[i1_14] != 4 ) ) ? ( 0 - 1 ) : ( ( ( char_at_1[i1_14] != 0 ) && ( char_at_1[i1_14] != 4 ) ) ? 1 : result_13 ) ) );
      break_15 = ( ( ( ( char_at_5[i1_14] != 0 ) && ( char_at_5[i1_14] != 4 ) ) || ( ( char_at_1[i1_14] != 0 ) && ( char_at_1[i1_14] != 4 ) ) ) ? 1 : break_15 );
      i1_14 = ( i1_14 + 1 );
      __VERIFIER_atomic_end();
    }
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( !break_15 && ( i1_14 <= 12 ) ));
    result_13 = ( !break_15 ? minus(index_of_4[4], index_of_0[4]) : result_13 );
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not ( ( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ) && !( index_of_4[4] == index_of_0[4] ) );
    result_13 = minus(index_of_4[4], index_of_0[4]);
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( last_index_of_7[3] == last_index_of_3[3] );
    i2_16 = 0;
    break_17 = 0;
    __VERIFIER_atomic_end();
    while (__VERIFIER_nondet_bool()) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not ( !break_17 && ( i2_16 <= 12 ) );
      result_13 = ( ( ( i2_16 != last_index_of_7[3] ) && ( ( ( char_at_5[i2_16] == 2 ) || ( char_at_5[i2_16] == 3 ) ) && ( ( char_at_1[i2_16] == 2 ) || ( char_at_1[i2_16] == 3 ) ) ) ) ? 0 : ( ( ( i2_16 != last_index_of_7[3] ) && ( ( char_at_5[i2_16] == 2 ) || ( char_at_5[i2_16] == 3 ) ) ) ? ( 0 - 1 ) : ( ( ( i2_16 != last_index_of_7[3] ) && ( ( char_at_1[i2_16] == 2 ) || ( char_at_1[i2_16] == 3 ) ) ) ? 1 : result_13 ) ) );
      break_17 = ( ( ( i2_16 != last_index_of_7[3] ) && ( ( char_at_5[i2_16] == 2 ) || ( ( char_at_5[i2_16] == 3 ) || ( ( char_at_1[i2_16] == 2 ) || ( char_at_1[i2_16] == 3 ) ) ) ) ) ? 1 : break_17 );
      __VERIFIER_atomic_end();
    }
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( !break_17 && ( i2_16 <= 12 ) ));
    result_13 = ( !break_17 ? minus(last_index_of_7[3], last_index_of_3[3]) : result_13 );
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not(!( last_index_of_7[3] == last_index_of_3[3] ));
    result_13 = minus(last_index_of_7[3], last_index_of_3[3]);
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) );
    assume_abort_if_not(!( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) ));
    result_13 = 1;
    __VERIFIER_atomic_end();
  }
  else if (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) ));
    assume_abort_if_not ( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) );
    result_13 = ( 0 - 1 );
    __VERIFIER_atomic_end();
  }
  else {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!( ( index_of_4[4] != ( 0 - 1 ) ) || ( index_of_0[4] != ( 0 - 1 ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_6[3] > 1 ) || ( ( count_occurrences_of_6[3] == 1 ) && ( index_of_4[2] != ( 0 - 1 ) ) ) ));
    assume_abort_if_not(!( ( count_occurrences_of_2[3] > 1 ) || ( ( count_occurrences_of_2[3] == 1 ) && ( index_of_0[2] != ( 0 - 1 ) ) ) ));
    result_13 = 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2;
  
  index_of_0 = create_fresh_int_array(5);
  index_of_4 = create_fresh_int_array(5);
  count_occurrences_of_2 = create_fresh_int_array(4);
  count_occurrences_of_6 = create_fresh_int_array(4);
  last_index_of_3 = create_fresh_int_array(4);
  last_index_of_7 = create_fresh_int_array(4);
  char_at_1 = create_fresh_int_array(13);
  char_at_5 = create_fresh_int_array(13);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  
  assume_abort_if_not(!( ( ( result_8 < 0 ) ? ( 0 - 1 ) : ( ( result_8 > 0 ) ? 1 : 0 ) ) == ( 0 - ( ( result_13 < 0 ) ? ( 0 - 1 ) : ( ( result_13 > 0 ) ? 1 : 0 ) ) ) ));
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