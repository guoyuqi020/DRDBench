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
void reach_error() { __assert_fail("0", "popl20-commit-1.wvr.c", 21, __extension__ __PRETTY_FUNCTION__); }
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

int *manager, *client, *node;
int client_size, client_front, client_back;
int manager_size, manager_front, manager_back;
int node_size, node_front, node_back;
int update, ok;
_Bool safe;

int *create_fresh_int_array(int size);

void* thread1(void* _argptr) {
  while (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(manager_back > manager_front && manager_front >= 0 && manager_front < manager_size);
    safe = safe && manager[manager_front] == update;
    manager_front++;
    __VERIFIER_atomic_end();
    
    __VERIFIER_atomic_begin();
    assume_abort_if_not(node_back >= 0 && node_back < node_size);
    assume_abort_if_not(node[node_back] == update);
    node_back++;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    assume_abort_if_not(manager_back > manager_front && manager_front >= 0 && manager_front < manager_size);
    safe = safe && manager[manager_front] == ok;
    manager_front++;
    __VERIFIER_atomic_end();
    
    __VERIFIER_atomic_begin();
    assume_abort_if_not(client_back >= 0 && client_back < client_size);
    assume_abort_if_not(client[client_back] == ok);
    client_back++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread2(void* _argptr) {
  while (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(node_back > node_front && node_front >= 0 && node_front < node_size);
    safe = safe && node[node_front] == update;
    node_front++;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    assume_abort_if_not(manager_back >= 0 && manager_back < manager_size);
    assume_abort_if_not(manager[manager_back] == ok);
    manager_back++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

void* thread3(void* _argptr) {
  while (__VERIFIER_nondet_bool()) {
    __VERIFIER_atomic_begin();
    assume_abort_if_not(manager_back >= 0 && manager_back < manager_size);
    assume_abort_if_not(manager[manager_back] == update);
    manager_back++;
    __VERIFIER_atomic_end();

    __VERIFIER_atomic_begin();
    assume_abort_if_not(client_back > client_front && client_front >= 0 && client_back < client_size);
    safe = safe && client[client_front] == ok;
    client_front++;
    __VERIFIER_atomic_end();
  }

  return 0;
}

int main() {
  pthread_t t1, t2, t3;

  safe = 1;
  
  manager_size = __VERIFIER_nondet_int();
  manager_front = __VERIFIER_nondet_int();
  manager_back = manager_front;
  manager = create_fresh_int_array(manager_size);
  
  client_front = __VERIFIER_nondet_int();
  client_back = client_front;
  client_size = __VERIFIER_nondet_int();
  client = create_fresh_int_array(client_size);
  
  node_front = __VERIFIER_nondet_int();
  node_back = node_front;
  node_size = __VERIFIER_nondet_int();
  node = create_fresh_int_array(node_size);
  
  ok = __VERIFIER_nondet_int();
  update = __VERIFIER_nondet_int();
  
  // main method
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  
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