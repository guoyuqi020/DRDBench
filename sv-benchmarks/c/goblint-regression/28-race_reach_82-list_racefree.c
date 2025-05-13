// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include<stdlib.h>
#define SVCOMP 1

#include <pthread.h>
#include <assert.h>

extern void abort(void);


void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }


extern int __VERIFIER_nondet_int();
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

pthread_mutex_t __global_lock = PTHREAD_MUTEX_INITIALIZER;

#define inc(x) do { pthread_mutex_lock(&__global_lock); (x)++; pthread_mutex_unlock(&__global_lock); } while (0)
#define dec(x) do { pthread_mutex_lock(&__global_lock); (x)--; pthread_mutex_unlock(&__global_lock); } while (0)

#define access(x) do { inc(x); dec(x); } while (0)

#define assert_racefree(x) do { pthread_mutex_lock(&__global_lock); __VERIFIER_assert((x) == 0); pthread_mutex_unlock(&__global_lock); } while (0)

#define access_or_assert_racefree(x) do { if (__VERIFIER_nondet_int()) access(x); else assert_racefree(x); } while (0)

#define N 10000
#define create_threads(t) pthread_t t##_ids[N]; for (int i=0; i<N; i++) pthread_create(&t##_ids[i], NULL, t##_fun, NULL)
#define join_threads(t) for (int i=0; i < N; i++) pthread_join (t##_ids[i], NULL)


struct s {
  int datum;
  struct s *next;
} *A;

void init (struct s *p) {
  p -> datum = 0;
  p -> next = NULL;
}

// Naive implementation of synchronized list library:
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

struct s *take(struct s *list) {
  pthread_mutex_lock(&list_mutex);
  struct s *p = list;
  while (p -> next != NULL && __VERIFIER_nondet_int()) p = p -> next;
  pthread_mutex_unlock(&list_mutex);
  return p;
}

void insert(struct s *node, struct s *list) {
  pthread_mutex_lock(&list_mutex);
  struct s *t = list->next;
  list->next = node;
  node->next = t;
  pthread_mutex_unlock(&list_mutex);
}

pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

void *t1_fun(void *arg) {
  struct s *p = malloc(sizeof(struct s));
  init(p);
  insert(p, A);
  return NULL;
}

void *t2_fun(void *arg) {
  struct s *p = take(A);
  pthread_mutex_lock(&data_mutex);
  access_or_assert_racefree(p->datum); // UNKNOWN
  pthread_mutex_unlock(&data_mutex);
  return NULL;
}

int main () {
  A = malloc(sizeof(struct s)); init(A);
  create_threads(t1);
  create_threads(t2);
  join_threads(t1);
  join_threads(t2);
  return 0;
}
