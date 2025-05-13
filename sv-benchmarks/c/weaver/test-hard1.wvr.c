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
void reach_error() { __assert_fail("0", "test-hard1.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

extern int  __VERIFIER_nondet_int(void);
extern unsigned int  __VERIFIER_nondet_uint(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

unsigned int p1, p2, m;
int n1, n2;

void* thread1(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = n1 > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (n1 > 0) {
      p1 = p1 + m;
      n1--;
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = n1 > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = n1 > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (n1 > 1) {
      p1 = p1 + 2 * m;
      n1 = n1 - 2;
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = n1 > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = n2 > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (n2 > 0) {
      p2 = p2 + m;
      n2--;
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = n2 > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread4(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = n2 > 0;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    if (n2 > 1) {
      p2 = p2 + 2 * m;
      n2 = n2 - 2;
    }
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = n2 > 0;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;
  
  p1 = __VERIFIER_nondet_uint();
  p2 = __VERIFIER_nondet_uint();
  n1 = __VERIFIER_nondet_int();
  n2 = __VERIFIER_nondet_int();
  m  = __VERIFIER_nondet_uint();
  assume_abort_if_not(p1 == p2 && n1 == n2);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);

  assume_abort_if_not(p1 != p2);
  reach_error();

  return 0;
}
