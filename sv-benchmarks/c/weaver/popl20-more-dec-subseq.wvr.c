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
void reach_error() { __assert_fail("0", "popl20-more-dec-subseq.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int *queue, *A;
int i, N, n, last, start, end, new, v_old;
_Bool ok;

int *create_fresh_int_array(int size);

void* thread1(void* _argptr) {
  while (i < N) {
    if (A[i] <= last) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(end >= 0 && end < n);
      assume_abort_if_not(queue[end] == A[i]);
      end++;
      __VERIFIER_atomic_end();
      last = A[i];
    }
    __VERIFIER_atomic_begin();
    i++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  __VERIFIER_atomic_begin();
  _Bool cond = i < N || start < end;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(start < end && start >= 0 && start < n);
    new = queue[start];
    start++;
    __VERIFIER_atomic_end();
    ok = ok && (v_old >= new);
    v_old = new;
    __VERIFIER_atomic_begin();
    cond = i < N || start < end;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2;
  
  ok = 1;
  N = __VERIFIER_nondet_int();
  n = __VERIFIER_nondet_int();
  start = __VERIFIER_nondet_int();
  end = start;
  queue = create_fresh_int_array(n);
  A = create_fresh_int_array(N);
  
  assume_abort_if_not(N > 0);
  v_old = A[0];
  last = v_old;
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  
  assume_abort_if_not(!ok);
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