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

int g = 0;

pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  // just for going to multithreaded mode
  return NULL;
}

int main() {
  pthread_mutex_lock(&A);
  g = 1;
  pthread_mutex_unlock(&A); // singlethreaded mode unlock

  g = 2;

  pthread_mutex_lock(&A);

  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL); // enter multithreaded mode with nonempty lockset

  g = 3; // write under mutex which was locked during singlethreaded mode
  __VERIFIER_assert(g == 3);
  return 0;
}
