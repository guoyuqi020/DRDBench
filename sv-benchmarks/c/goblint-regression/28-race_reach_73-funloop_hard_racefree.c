// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include<pthread.h>
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


struct cache_entry {
  int refs;
  pthread_mutex_t refs_mutex;
} cache[10];

void cache_entry_addref(struct cache_entry *entry) {
  pthread_mutex_lock(&entry->refs_mutex);
  access_or_assert_racefree(entry->refs); // TODO
  pthread_mutex_unlock(&entry->refs_mutex);
}

void *t_fun(void *arg) {
  int i;
  for(i=0; i<10; i++) cache_entry_addref(&cache[i]);
  return NULL;
}

int main () {
  for (int i = 0; i < 10; i++)
    pthread_mutex_init(&cache[i].refs_mutex, NULL);

  int i;
  create_threads(t);

  for(i=0; i<10; i++) cache_entry_addref(&cache[i]);

  pthread_mutex_lock(&cache[5].refs_mutex);
  access_or_assert_racefree(cache[5].refs); // TODO
  pthread_mutex_unlock(&cache[5].refs_mutex);

  join_threads(t);
  return 0;
}
