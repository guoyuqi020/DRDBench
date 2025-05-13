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
void reach_error() { __assert_fail("0", "array-eq-trans.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_join (pthread_t __th, void **__thread_return);

typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int  __VERIFIER_nondet_int(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

int *A;
int *B;
int *C;
int i_AB, i_BC, i_AC, An, Bn, Cn;

int *create_fresh_int_array(int size);

void* thread1(void* _argptr) {
  while (i_AB < An && i_AB < Bn) {
    if (A[i_AB] == B[i_AB]) {
      i_AB++;
    } else {
      break;
    }
  }
  return 0;
}

void* thread2(void* _argptr) {
  while (i_BC < Bn && i_BC < Cn) {
    if (B[i_BC] == C[i_BC]) {
      i_BC++;
    } else {
      break;
    }
  }
  return 0;
}

void* thread3(void* _argptr) {
  while (i_AC < An && i_AC < Cn) {
    if (A[i_AC] == C[i_AC]) {
      i_AC++;
    } else {
      break;
    }
  }
  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  // initialize global variables
  An = __VERIFIER_nondet_int();
  Bn = __VERIFIER_nondet_int();
  Cn = __VERIFIER_nondet_int();
  A = create_fresh_int_array(An);
  B = create_fresh_int_array(Bn);
  C = create_fresh_int_array(Cn);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  
  assume_abort_if_not(i_AB == An || (i_AB < Bn && A[i_AB] <= B[i_AB]));
  assume_abort_if_not(i_BC == Bn || (i_BC < Cn && B[i_BC] <= C[i_BC]));
  assume_abort_if_not(!(i_AC == An || (i_AC < Cn && A[i_AC] <= C[i_AC])));
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