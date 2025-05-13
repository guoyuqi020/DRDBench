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
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg )
{
  while (1) {
    pthread_mutex_lock(&A);
    g = 1000;
    __VERIFIER_assert(g != 0);
    if (g > 0) {
      g--;
    }
    pthread_mutex_unlock(&A);
    // extra mutex makes mine-W more precise than lock
    pthread_mutex_lock(&B);
    pthread_mutex_unlock(&B);
  }
  return NULL;
}

int main(int argc , char **argv )
{
  pthread_t tid;
  pthread_create(& tid, NULL, & worker, NULL);
  return 0;
}
