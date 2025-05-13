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
void reach_error() { __assert_fail("0", "parallel-bakery-4.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

_Bool e1, e2, e3, e4;
int n1, n2, n3, n4, i, i1, i2, i3, i4;

void* thread1(void* _argptr) {
  __VERIFIER_atomic_begin();
  e1 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n1 = (n1 < n2) ? n2 : n1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n1 = (n1 < n3) ? n3 : n1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n1 = (n1 < n4) ? n4 : n1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n1++;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  e1 = 0;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e2);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n2 != 0 ) && ( ( n2 < n1 ) || ( ( n2 == n1 ) && ( 2 < 1 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e3);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n3 != 0 ) && ( ( n3 < n1 ) || ( ( n3 == n1 ) && ( 3 < 1 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e4);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n4 != 0 ) && ( ( n4 < n1 ) || ( ( n4 == n1 ) && ( 4 < 1 ) ) ) ) );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  i1 = i;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  i = i1 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n1 = 0;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  e2 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n2 = (n2 < n1) ? n1 : n2;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n2 = (n2 < n3) ? n3 : n2;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n2 = (n2 < n4) ? n4 : n2;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n2++;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  e2 = 0;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e1);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n1 != 0 ) && ( ( n1 < n2 ) || ( ( n1 == n2 ) && ( 1 < 2 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e3);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n3 != 0 ) && ( ( n3 < n2 ) || ( ( n3 == n2 ) && ( 3 < 2 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e4);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n4 != 0 ) && ( ( n4 < n2 ) || ( ( n4 == n2 ) && ( 4 < 2 ) ) ) ) );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  i2 = i;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  i = i2 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n2 = 0;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  e3 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n3 = (n3 < n1) ? n1 : n3;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n3 = (n3 < n2) ? n2 : n3;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n3 = (n3 < n4) ? n4 : n3;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n3++;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  e3 = 0;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e1);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n1 != 0 ) && ( ( n1 < n3 ) || ( ( n1 == n3 ) && ( 1 < 3 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e2);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n2 != 0 ) && ( ( n2 < n3 ) || ( ( n2 == n3 ) && ( 2 < 3 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e4);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n4 != 0 ) && ( ( n4 < n3 ) || ( ( n4 == n3 ) && ( 4 < 3 ) ) ) ) );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  i3 = i;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  i = i3 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n3 = 0;
  __VERIFIER_atomic_end();

  return 0;
}

void* thread4(void* _argptr) {
  __VERIFIER_atomic_begin();
  e4 = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n4 = (n4 < n1) ? n1 : n4;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n4 = (n4 < n2) ? n2 : n4;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n4 = (n4 < n3) ? n3 : n4;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n4++;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  e4 = 0;
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e1);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n1 != 0 ) && ( ( n1 < n4 ) || ( ( n1 == n4 ) && ( 1 < 4 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e2);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n2 != 0 ) && ( ( n2 < n4 ) || ( ( n2 == n4 ) && ( 2 < 4 ) ) ) ) );
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not(!e3);
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  assume_abort_if_not( !( ( n3 != 0 ) && ( ( n3 < n4 ) || ( ( n3 == n4 ) && ( 3 < 4 ) ) ) ) );
  __VERIFIER_atomic_end();

  __VERIFIER_atomic_begin();
  i4 = i;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  i = i4 + 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  n4 = 0;
  __VERIFIER_atomic_end();

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;

  // initialize global variables
  e1 = __VERIFIER_nondet_bool();
  e2 = __VERIFIER_nondet_bool();
  e3 = __VERIFIER_nondet_bool();
  e4 = __VERIFIER_nondet_bool();
  n1 = __VERIFIER_nondet_int();
  n2 = __VERIFIER_nondet_int();
  n3 = __VERIFIER_nondet_int();
  n4 = __VERIFIER_nondet_int();
  i  = __VERIFIER_nondet_int();
  i1 = __VERIFIER_nondet_int();
  i2 = __VERIFIER_nondet_int();
  i3 = __VERIFIER_nondet_int();
  i4 = __VERIFIER_nondet_int();

  // main method
  assume_abort_if_not( ( i == 0 ) && ( e1 == 0 ) && ( e2 == 0 ) && ( e3 == 0 ) && ( e4 == 0 ) && ( n1 == 0 ) && ( n2 == 0 ) && ( n3 == 0 ) && ( n4 == 0 ) );

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);

  assume_abort_if_not( i != 4 );
  reach_error();

  return 0;
}
