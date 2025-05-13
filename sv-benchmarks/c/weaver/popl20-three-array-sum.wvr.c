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
void reach_error() { __assert_fail("0", "popl20-three-array-sum.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int  __VERIFIER_nondet_int(void);
extern unsigned int  __VERIFIER_nondet_uint(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

unsigned int *A, *B, *C;
unsigned int asum, bsum, csum;
int N, p;

unsigned int *create_fresh_uint_array(int size);

void* thread1(void* _argptr) {
  for (int i=0; i<N; i++) {
    asum = asum + A[i];
    bsum = bsum + B[i];
  }

  return 0;
}

void* thread2(void* _argptr) {
  for (int i=0; i<N; i++) {
    __VERIFIER_atomic_begin();
    C[i] = A[i] + B[i];
    p = i + 1;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  int i = 0;
  while (i < N) {
    __VERIFIER_atomic_begin();
    _Bool cond = i < p;
    __VERIFIER_atomic_end();
    if (cond) {
      __VERIFIER_atomic_begin();
      csum = csum + C[i];
      __VERIFIER_atomic_end();
      i++;
    }
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  N = __VERIFIER_nondet_int();
  A = create_fresh_uint_array(N);
  B = create_fresh_uint_array(N);
  C = create_fresh_uint_array(N);

  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);

  assume_abort_if_not(csum != asum + bsum);
  reach_error();

  return 0;
}

unsigned int *create_fresh_uint_array(int size) {
  assume_abort_if_not(size >= 0);
  assume_abort_if_not(size <= (((size_t) 4294967295) / sizeof(unsigned int)));

  unsigned int* arr = (unsigned int*)malloc(sizeof(unsigned int) * (size_t)size);
  for (int i = 0; i < size; i++) {
    arr[i] = __VERIFIER_nondet_uint();
  }
  return arr;
}
