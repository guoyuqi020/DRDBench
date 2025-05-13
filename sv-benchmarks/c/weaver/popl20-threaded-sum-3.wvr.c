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
void reach_error() { __assert_fail("0", "popl20-threaded-sum-3.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern unsigned int  __VERIFIER_nondet_uint(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

unsigned int s, t, m, c, T, S, u, U;

void* thread1(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = s > 0 || t > 0 || u > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (s > 0) {
      s--;
      m++;    
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = s > 0 || t > 0 || u > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = t > 0 || u > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (t > 0) {
      t--;
      s++;    
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = t > 0 || u > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = u > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    t++;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    u--;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = u > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3;
  
  S = __VERIFIER_nondet_uint();
  T = __VERIFIER_nondet_uint();
  U = __VERIFIER_nondet_uint();
  s = S;
  t = T;
  u = U;

  assume_abort_if_not(S > 0 && T > 0 && U > 0);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);;
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not(m != S + T + U);
  reach_error();

  return 0;
}
