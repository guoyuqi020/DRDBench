// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <pthread.h>
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


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  int *p = (int *) arg;
  pthread_mutex_lock(&mutex1);
  access(*p);
  pthread_mutex_unlock(&mutex1);
  return NULL;
}

int main(void) {
  pthread_t id;
  int i = 0;
  pthread_create(&id, NULL, t_fun, (void *) &i);
  pthread_mutex_lock(&mutex1);
  assert_racefree(i);
  pthread_mutex_unlock(&mutex1);
  pthread_join(id, NULL);
  return 0;
}
