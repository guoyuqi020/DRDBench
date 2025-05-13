// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <pthread.h>
#include <stdio.h>

extern void exit (int status);

int glob;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bad   = PTHREAD_MUTEX_INITIALIZER;

void f(pthread_mutex_t *m) {
  pthread_mutex_lock(m);
  glob++; // RACE!
  pthread_mutex_unlock(m);
  exit(0);
}

void *t_fun(void *arg) {
  pthread_mutex_lock(&mutex);
  glob++; // RACE!
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void) {
  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);
  while (1) {
    f(&bad);
  }
  
  glob = 8;
  return 0;
}
