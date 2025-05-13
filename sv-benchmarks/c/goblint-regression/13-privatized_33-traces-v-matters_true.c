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

int g = 0; // doesn't matter, gets always overwritten
pthread_mutex_t C = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t D = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t E = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  pthread_mutex_lock(&C);
  pthread_mutex_lock(&E);
  g = 42;
  pthread_mutex_lock(&D);
  pthread_mutex_unlock(&E);
  pthread_mutex_unlock(&C);
  pthread_mutex_unlock(&D);
  return NULL;
}

int main(void) {
  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);

  pthread_mutex_lock(&C);
  pthread_mutex_lock(&D);
  g = 2;
  pthread_mutex_unlock(&C);
  pthread_mutex_lock(&E);
  __VERIFIER_assert(g == 2);
  return 0;
}
