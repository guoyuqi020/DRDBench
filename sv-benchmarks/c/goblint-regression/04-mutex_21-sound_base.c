// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <pthread.h>
#include <stdio.h>

int global;

void bad() { global++; } // RACE!
void good() { printf("Hello!"); }

void (*f)() = good;

void *t_fun(void *arg) {
  f(); // RACE!
  return NULL;
}

int main() {
  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);
  f = bad; // RACE!
  printf("global: %d\n", global); // RACE!
  return 0;
}
