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
void reach_error() { __assert_fail("0", "parallel-barrier.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int   __VERIFIER_nondet_int(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void  __VERIFIER_atomic_begin();
extern void  __VERIFIER_atomic_end();

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int x_0, y_1;
_Bool f1_2, f2_3;
int temp_4, temp_5;
int x_6, x_7;
_Bool f1_8, f2_9;
int temp_10, temp_11;
int y_7;

void* thread2(void* _argptr) {
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
  assume_abort_if_not( f1_2 && f2_3 );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  temp_4 = y_1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y_1 = temp_4 + 1;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  temp_5 = y_1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y_1 = temp_5 + 1;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  f2_3 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( f1_2 && f2_3 );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  temp_5 = x_0;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x_0 = temp_5 + 1;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread1(void* _argptr) {
  pthread_t t2, t3;

  assume_abort_if_not( x_0 == y_1 && !f1_2 && !f2_3 );

  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  return 0;
}

void* thread5(void* _argptr) {
  __VERIFIER_atomic_begin();
  temp_10 = x_6;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x_6 = temp_10 + 1;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  f1_8 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( f1_8 && f2_9 );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  temp_10 = y_7;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y_7 = temp_10 + 1;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread6(void* _argptr) {
  __VERIFIER_atomic_begin();
  temp_11 = y_7;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  y_7 = temp_11 + 1;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  f2_9 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( f1_8 && f2_9 );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  temp_11 = x_6;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  x_6 = temp_11 + 1;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread4(void* _argptr) {
  pthread_t t5, t6;

  assume_abort_if_not( x_6 == y_7 && !f1_8 && !f2_9 );

  pthread_create(&t5, 0, thread5, 0);
  pthread_create(&t6, 0, thread6, 0);
  pthread_join(t5, 0);
  pthread_join(t6, 0);

  return 0;
}

int main() {
  pthread_t t1, t4;

  // initialize global variables
  x_0 = __VERIFIER_nondet_int();
  y_1 = __VERIFIER_nondet_int();
  f1_2 = __VERIFIER_nondet_bool();
  f2_3 = __VERIFIER_nondet_bool();
  temp_4 = __VERIFIER_nondet_int();
  temp_5 = __VERIFIER_nondet_int();
  x_6 = __VERIFIER_nondet_int();
  x_7 = __VERIFIER_nondet_int();
  f1_8 = __VERIFIER_nondet_bool();
  f2_9 = __VERIFIER_nondet_bool();
  temp_10 = __VERIFIER_nondet_int();
  temp_11 = __VERIFIER_nondet_int();

  // main method
  assume_abort_if_not( ( x_0 == x_6 ) && ( y_1 == y_7 ) );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t4, 0);

  assume_abort_if_not( !( ( x_0 == x_6 ) && ( y_1 == y_7 ) ) );
  reach_error();

  return 0;
}