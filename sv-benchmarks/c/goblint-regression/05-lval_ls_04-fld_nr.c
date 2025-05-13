// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <pthread.h>

int glob;

struct {
  pthread_mutex_t x;
  pthread_mutex_t y;
} m;

void *t_fun(void *arg) {
  pthread_mutex_lock(&m.x);
  glob++; // NORACE
  pthread_mutex_unlock(&m.x);
  return NULL;
}

int main() {
  pthread_mutex_init(&m.x, NULL);
  pthread_mutex_init(&m.y, NULL);

  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);
  pthread_mutex_lock(&m.x);
  glob++; // NORACE
  pthread_mutex_unlock(&m.x);
  return 0;
}


