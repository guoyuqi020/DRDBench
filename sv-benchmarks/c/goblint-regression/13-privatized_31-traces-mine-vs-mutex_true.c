// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <assert.h>
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

#include <pthread.h>

int g;
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  pthread_mutex_lock(&A);
  pthread_mutex_lock(&B);
  g++;
  pthread_mutex_unlock(&B); // Write Mine influence: [[g, B], t2_fun, {A}] -> 1
  pthread_mutex_lock(&B);
  g--;
  pthread_mutex_unlock(&B); // Write Mine influence: [[g, B], t2_fun, {A}] -> 0
  pthread_mutex_unlock(&A);
  return NULL;
}

int main(void) {
  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);

  pthread_mutex_lock(&B); // Read & join to g Mine influence: [[g, B], t2_fun, {A}] -> (0 join 1 = Unknown)
  pthread_mutex_unlock(&B);

  pthread_mutex_lock(&A);
  pthread_mutex_lock(&B);
  __VERIFIER_assert(g == 0);
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);

  pthread_join(id, NULL);
  return 0;
}