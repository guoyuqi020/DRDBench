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

extern int __VERIFIER_nondet_int();

#include <pthread.h>

int g = 42; // matches write in t_fun
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  pthread_mutex_lock(&A);
  pthread_mutex_lock(&B);
  g = 42;
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);
  return NULL;
}

int main(void) {
  int r = __VERIFIER_nondet_int(); //rand
  int t;

  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);

  pthread_mutex_lock(&A);
  pthread_mutex_lock(&B);
  if (r) {
    g = 17;
    pthread_mutex_unlock(&B); // publish to g#prot
    pthread_mutex_lock(&B);
  }
  // locally written g is only in one branch, g == g#prot should be forgotten!
  t = g;
  __VERIFIER_assert(t == 17);
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);
  return 0;
}
