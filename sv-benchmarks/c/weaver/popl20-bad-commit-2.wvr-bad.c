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
void reach_error() { __assert_fail("0", "popl20-bad-commit-2.wvr-bad.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int *manager, *client, *node1, *node2;
int client_size, client_front, client_back, client_state;
int manager_size, manager_front, manager_back, manager_state;
int node1_size, node1_front, node1_back, node1_state;
int node2_size, node2_front, node2_back, node2_state;
int update, ok;
_Bool safe;

int *create_fresh_int_array(int size);

void* thread1() {
  while (__VERIFIER_nondet_bool()) {
    if (manager_state == 0) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back > manager_front && manager_front >= 0 && manager_front < manager_size);
      safe = manager[manager_front] == update;
      manager_front++;
      manager_state = 1;
      __VERIFIER_atomic_end();
    } else if (manager_state == 1){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(node1_back >= 0 && node1_back < node1_size);
      assume_abort_if_not(node1[node1_back] == update);
      node1_back++;
      manager_state = 2;
      __VERIFIER_atomic_end();
    } else if (manager_state == 2) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(node2_back >= 0 && node2_back < node2_size);
      assume_abort_if_not(node2[node2_back] == update);
      node2_back++;
      manager_state = 3;
      __VERIFIER_atomic_end();
    } else if (manager_state == 3){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back > manager_front && manager_front >= 0 && manager_front < manager_size);
      safe = manager[manager_front] == ok;
      manager_front++;
      manager_state = 4;
      __VERIFIER_atomic_end();
    } else if (manager_state == 4){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back > manager_front && manager_front >= 0 && manager_front < manager_size);
      safe = manager[manager_front] == ok;
      manager_front++;
      manager_state = 5;
      __VERIFIER_atomic_end();
    } else if (manager_state == 5){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(client_back >= 0 && client_back < client_size);
      assume_abort_if_not(client[client_back] == ok);
      client_back++;
      manager_state = 0;
      __VERIFIER_atomic_end();
    }
  }

  return 0;
}

void* thread2() {
  while (__VERIFIER_nondet_bool()) {
    if (node1_state == 0) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(node1_back > node1_front && node1_front >= 0 && node1_front < node1_size);
      safe = node1[node1_front] == update;
      node1_front++;
      node1_state = 1;
      __VERIFIER_atomic_end();
    } else if (node1_state == 1){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back >= 0 && manager_back < manager_size);
      assume_abort_if_not(manager[manager_back] == ok);
      manager_back++;
      node1_state = 0;
      __VERIFIER_atomic_end();
    }
  }

  return 0;
}

void* thread3() {
  while (__VERIFIER_nondet_bool()) {
    if (node2_state == 0) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(node2_back > node2_front && node2_front >= 0 && node2_front < node2_size);
      safe = node2[node2_front] == update;
      node2_front++;
      node2_state = 1;
      __VERIFIER_atomic_end();
    } else if (node2_state == 1) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back >= 0 && manager_back < manager_size);
      assume_abort_if_not(manager[manager_back] == ok);
      manager_back++;
      node2_state = 0;
      __VERIFIER_atomic_end();
    }
  }

  return 0;
}

void* thread4() {
  while (__VERIFIER_nondet_bool()) {
    if (client_state == 0) {
      __VERIFIER_atomic_begin();
      assume_abort_if_not(manager_back >= 0 && manager_back < manager_size);
      assume_abort_if_not(manager[manager_back] == update);
      manager_back++;
      client_state = 1;
      __VERIFIER_atomic_end();
    } else if (client_state == 1){
      __VERIFIER_atomic_begin();
      assume_abort_if_not(client_back > client_front && client_front >= 0 && client_back < client_size);
      safe = client[client_front] == ok;
      client_front++;
      client_state = 0;
      __VERIFIER_atomic_end();
    }
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3, t4;

  safe = 1;
  
  manager_size = __VERIFIER_nondet_int();
  manager_front = __VERIFIER_nondet_int();
  manager_back = manager_front;
  manager = create_fresh_int_array(manager_size);
  
  client_front = __VERIFIER_nondet_int();
  client_back = client_front;
  client_size = __VERIFIER_nondet_int();
  client = create_fresh_int_array(client_size);
  
  node1_front = __VERIFIER_nondet_int();
  node1_back = node1_front;
  node1_size = __VERIFIER_nondet_int();
  node1 = create_fresh_int_array(node1_size);
  
  node2_front = __VERIFIER_nondet_int();
  node2_back = node2_front;
  node2_size = __VERIFIER_nondet_int();
  node2 = create_fresh_int_array(node2_size);
  
  ok = __VERIFIER_nondet_int();
  update = __VERIFIER_nondet_int();
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_create(&t4, 0, thread4, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  pthread_join(t4, 0);
  
  assume_abort_if_not(!safe);
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