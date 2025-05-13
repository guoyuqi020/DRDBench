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

int g = 1;
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  pthread_mutex_lock(&A);
  g = 2; // write something non-initial so base wouldn't find success
  __VERIFIER_assert(g == 2);
  pthread_mutex_unlock(&A);
  return NULL;
}

int main(void) {
  int x, y;

  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);

  pthread_mutex_lock(&A);
  x = g;
  y = g;
  __VERIFIER_assert(x == y);
  pthread_mutex_unlock(&A);

  // g = g - g - x;
  return 0;
}
