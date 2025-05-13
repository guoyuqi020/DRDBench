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

int g = 42;
int h = 42;
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  int x = __VERIFIER_nondet_int(); //rand
  if (x > -1000) { // avoid underflow
    pthread_mutex_lock(&B);
    pthread_mutex_lock(&A);
    g = x;
    h = x - 17;
    pthread_mutex_unlock(&A);
    pthread_mutex_lock(&A);
    h = x;
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&B);
  }
  return NULL;
}

void *t2_fun(void *arg) {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand
  pthread_mutex_lock(&A);
  x = g;
  y = h;
  pthread_mutex_unlock(&A);
  __VERIFIER_assert(y <= x);
  return NULL;
}

void *t3_fun(void *arg) {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand
  pthread_mutex_lock(&B);
  pthread_mutex_lock(&A);
  x = g;
  y = h;
  pthread_mutex_unlock(&A);
  pthread_mutex_unlock(&B);
  __VERIFIER_assert(y == x);
  return NULL;
}

int main(void) {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand

  pthread_t id, id2, id3;
  pthread_create(&id, NULL, t_fun, NULL);
  pthread_create(&id2, NULL, t2_fun, NULL);
  pthread_create(&id3, NULL, t3_fun, NULL);

  // thread 4
  pthread_mutex_lock(&A);
  x = g;
  y = h;
  pthread_mutex_lock(&B);
  __VERIFIER_assert(y == x);
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);
  __VERIFIER_assert(y == x);
  return 0;
}
