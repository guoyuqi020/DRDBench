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
void reach_error() { __assert_fail("0", "popl20-prod-cons3.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int *queue1, *queue2;
int front1, back1, front2, back2, d1, d2, n1, n2, W;
_Bool v_assert;

int *create_fresh_int_array(int size);

void* thread1(void* _argptr) {
  for (int w=W; w>0; w--) {
    __VERIFIER_atomic_begin();
    _Bool cond = v_assert;
    __VERIFIER_atomic_end();
    if (!cond) {
      break;
    }
    __VERIFIER_atomic_begin();
    assume_abort_if_not(back1 >= 0 && back1 < n1);
    assume_abort_if_not(queue1[back1] == 1);
    back1++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  int temp;
  __VERIFIER_atomic_begin();
  _Bool cond = v_assert;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(front1 < back1 && front1 >= 0 && front1 < n1);
    temp = queue1[front1];
    front1++;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    assume_abort_if_not(back2 >= 0 && back2 < n2);
    assume_abort_if_not(queue2[back2] == temp + 1);
    back2++;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    d1 = d1 + temp;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = v_assert;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  int temp;
  __VERIFIER_atomic_begin();
  _Bool cond = v_assert;
  __VERIFIER_atomic_end();
  while (cond) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(front2 < back2 && front2 >= 0 && front2 < n2);
    temp = queue2[front2];
    front2++;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    d2 = d2 + temp;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    cond = v_assert;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread4(void* _argptr) {
  __VERIFIER_atomic_begin();
  v_assert = (d2 <= 2*W);
  __VERIFIER_atomic_end();

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;
  
  W = __VERIFIER_nondet_int();
  assume_abort_if_not(W < 2147483647/2);
  n1 = __VERIFIER_nondet_int();
  n2 = __VERIFIER_nondet_int();
  front1 = __VERIFIER_nondet_int();
  front2 = __VERIFIER_nondet_int();
  back1 = front1;
  back2 = front2;
  v_assert = 1;
  queue1 = create_fresh_int_array(n1);
  queue2 = create_fresh_int_array(n2);
  
  assume_abort_if_not(W >= 0);
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);
  
  assume_abort_if_not(!v_assert);
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
