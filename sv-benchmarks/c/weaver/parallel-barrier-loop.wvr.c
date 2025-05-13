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
void reach_error() { __assert_fail("0", "parallel-barrier-loop.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern unsigned int __VERIFIER_nondet_uint(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void  __VERIFIER_atomic_begin();
extern void  __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

unsigned int x_0, y_1, x_8, y_9;
_Bool f1_2, f2_3, f1_10, f2_11;
unsigned int temp_4, temp_5, temp_6, temp_7, temp_12, temp_13, temp_14, temp_15;


void* thread2(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    temp_4 = x_0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    x_0 = temp_4 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f1_2 = 1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(f2_3);
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    temp_5 = y_1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    y_1 = temp_5 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f1_2 = 0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!f2_3);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    temp_6 = y_1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    y_1 = temp_6 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f2_3 = 1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(f1_2);
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    temp_7 = x_0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    x_0 = temp_7 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f2_3 = 0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!f1_2);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread1(void* _argptr) {
  pthread_t t2, t3;

  __VERIFIER_atomic_begin();
  f1_2 = 0;
  f2_3 = 0;
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
    temp_12 = x_8;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    x_8 = temp_12 + 1;
    __VERIFIER_atomic_end();
 
    __VERIFIER_atomic_begin();
    f1_10 = 1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(f2_11);
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    temp_13 = y_9;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    y_9 = temp_13 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f1_10 = 0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!f2_11);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread6(void* _argptr) {
  while ( __VERIFIER_nondet_bool() ) {
    __VERIFIER_atomic_begin();
    temp_14 = y_9;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    y_9 = temp_14 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f2_11 = 1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(f1_10);
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    temp_15 = x_8;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    x_8 = temp_15 + 1;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    f2_11 = 0;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(!f1_10);
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread4(void* _argptr) {
  pthread_t t5, t6;

  __VERIFIER_atomic_begin();
  f1_10 = 0;
  f2_11 = 0;
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
  x_0 = __VERIFIER_nondet_uint();
  y_1 = __VERIFIER_nondet_uint();
  x_8 = __VERIFIER_nondet_uint();
  y_9 = __VERIFIER_nondet_uint();
  temp_4  = __VERIFIER_nondet_uint();
  temp_5  = __VERIFIER_nondet_uint();
  temp_6  = __VERIFIER_nondet_uint();
  temp_7  = __VERIFIER_nondet_uint();
  temp_12 = __VERIFIER_nondet_uint();
  temp_13 = __VERIFIER_nondet_uint();
  temp_14 = __VERIFIER_nondet_uint();
  temp_15 = __VERIFIER_nondet_uint();
  f1_2  = __VERIFIER_nondet_bool();
  f2_3  = __VERIFIER_nondet_bool();
  f1_10 = __VERIFIER_nondet_bool();
  f2_11 = __VERIFIER_nondet_bool();

  // main method
  assume_abort_if_not( ( x_0 == x_8 ) && ( y_1 == y_9 ) );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t4, 0);

  assume_abort_if_not( !( ( x_0 == x_8 ) && ( y_1 == y_9 ) ) );
  reach_error();

  return 0;
}