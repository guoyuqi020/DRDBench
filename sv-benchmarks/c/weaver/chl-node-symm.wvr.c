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
void reach_error() { __assert_fail("0", "chl-node-symm.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int id_0, id_3, result_6, order1_7, order2_8, result_9, order1_10, order2_11;
int *get_2, *get_5;
_Bool *contains_key_1, *contains_key_4;

int *create_fresh_int_array(int size);
_Bool *create_fresh_bool_array(int size);
int minus(int a, int b);

void* thread1(void* _argptr) {
  order1_7 = get_2[id_0];
  order2_8 = get_5[id_3];
  result_6 = ( ( contains_key_1[id_0] && contains_key_4[id_3] ) ? ( ( order1_7 < order2_8 ) ? -1 : ( ( order1_7 > order2_8 ) ? 1 : 0 ) ) : minus(get_2[id_0], get_5[id_3]) );

  return 0;
}

void* thread2(void* _argptr) {
  order1_10 = get_5[id_3];
  order2_11 = get_2[id_0];
  result_9 = ( ( contains_key_4[id_3] && contains_key_1[id_0] ) ? ( ( order1_10 < order2_11 ) ? -1 : ( ( order1_10 > order2_11 ) ? 1 : 0 ) ) : minus(get_5[id_3], get_2[id_0]) );

  return 0;
}


int main() {
  pthread_t t1, t2;

  // initialize global variables
  id_0 = __VERIFIER_nondet_int();
  assume_abort_if_not(id_0 >= 0);
  id_3 = __VERIFIER_nondet_int();
  assume_abort_if_not(id_3 >= 0);
  result_6 = __VERIFIER_nondet_int();
  order1_7 = __VERIFIER_nondet_int();
  order2_8 = __VERIFIER_nondet_int();
  result_9 = __VERIFIER_nondet_int();
  order1_10 = __VERIFIER_nondet_int();
  order2_11 = __VERIFIER_nondet_int();
  assume_abort_if_not(id_0 < 2147483647 && id_3 < 2147483647);
  get_2 = create_fresh_int_array(id_0 + 1);
  get_5 = create_fresh_int_array(id_3 + 1);
  contains_key_1 = create_fresh_bool_array(id_0+1);
  contains_key_4 = create_fresh_bool_array(id_3+1);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assume_abort_if_not( !( ( ( result_6 < 0 ) ? ( - 1 ) : ( ( result_6 > 0 ) ? 1 : 0 ) ) == ( 0 - ( ( result_9 < 0 ) ? ( - 1 ) : ( ( result_9 > 0 ) ? 1 : 0 ) ) ) ) );
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