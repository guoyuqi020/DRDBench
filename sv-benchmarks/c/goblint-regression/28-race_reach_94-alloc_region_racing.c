// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
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

void init (struct s *p, int x) {
  p -> datum = x;
  p -> next = NULL;
}

void insert(struct s *p, struct s **list) {
  p->next = *list;
  *list = p;
}

pthread_mutex_t A_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B_mutex = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  struct s *p = malloc(sizeof(struct s));
  init(p,7);

  pthread_mutex_lock(&A_mutex);
  insert(p, &A);
  pthread_mutex_unlock(&A_mutex);

  pthread_mutex_lock(&B_mutex);
  access_or_assert_racefree(p->datum); // UNKNOWN
  pthread_mutex_unlock(&B_mutex);
  return NULL;
}

int main () {
  struct s *p;
  A = malloc(sizeof(struct s));
  init(A,3);

  create_threads(t);

  p = malloc(sizeof(struct s));
  init(p,9);

  pthread_mutex_lock(&A_mutex);
  insert(p, &A);
  pthread_mutex_unlock(&A_mutex);

  pthread_mutex_lock(&A_mutex);
  p = A;
  while (p->next) {
    access_or_assert_racefree(p->datum); // UNKNOWN
    p = p->next;
  }
  pthread_mutex_unlock(&A_mutex);

  join_threads(t);
  return 0;
}
