// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2023 University of Tartu
//
// SPDX-License-Identifier: MIT

// Per-thread structs containing thread ID passed via argument.
// Extracted from chrony.
#include <stdlib.h>
#include <pthread.h>
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern int __VERIFIER_nondet_int();

struct thread {
  pthread_t tid;
  int data;
};

void *thread(void *arg) {
  struct thread *t = arg;
  t->data = __VERIFIER_nondet_int(); // NORACE
  return NULL;
}

int main() {
  int threads_total = __VERIFIER_nondet_int();
  assume_abort_if_not(threads_total >= 0);

  struct thread **ts = malloc(threads_total * sizeof(struct thread *));

  // create threads
  for (int i = 0; i < threads_total; i++) {
    struct thread *t = malloc(sizeof(struct thread));
    ts[i] = t;
    pthread_create(&t->tid, NULL, &thread, t); // may fail but doesn't matter
  }

  // join threads
  for (int i = 0; i < threads_total; i++) {
    pthread_join(ts[i]->tid, NULL);
    free(ts[i]);
  }

  free(ts);

  return 0;
}
