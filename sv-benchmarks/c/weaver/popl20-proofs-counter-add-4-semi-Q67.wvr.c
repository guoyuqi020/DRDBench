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
void reach_error() { __assert_fail("0", "popl20-proofs-counter-add-4-semi-Q67.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int  __VERIFIER_nondet_int(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int i1, i2, N1, N2, counter, j1, j2, M1, M2;

void* thread1(void* _argptr) {
  while (i1 < N1) {
    __VERIFIER_atomic_begin();
    counter++;
    i1++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  while (i2 < N2) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(0 < counter);
    counter--;
    i2++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  while (j1 < M1) {
    __VERIFIER_atomic_begin();
    counter++;
    j1++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread4(void* _argptr) {
  while (j2 < M2) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(0 < counter);
    counter--;
    j2++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;
  
  N1 = __VERIFIER_nondet_int();
  N2 = __VERIFIER_nondet_int();
  M1 = __VERIFIER_nondet_int();
  M2 = __VERIFIER_nondet_int();
  assume_abort_if_not(N1 == N2 && N1 == M1 && N1 == M2);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);
  
  assume_abort_if_not(counter != 0);
  reach_error();

  return 0;
}