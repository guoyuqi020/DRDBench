// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2023 University of Tartu
//
// SPDX-License-Identifier: MIT

// Per-thread array index using bitmask passed via argument.
// Extracted from concrat/nnn.
#include <stdlib.h>
#include <pthread.h>
#include <strings.h>
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern int __VERIFIER_nondet_int();

int threads_mask = -1; // all bits 1
pthread_mutex_t threads_mask_mutex = PTHREAD_MUTEX_INITIALIZER;

int *datas;

void *thread(void *arg) {
  int j = (int)arg;
  pthread_mutex_lock(&threads_mask_mutex);
  // change j-th bit back to 1
  threads_mask |= 1 << j; // NORACE
  pthread_mutex_unlock(&threads_mask_mutex);

  datas[j] = __VERIFIER_nondet_int(); // RACE!
  return NULL;
}

int main() {
  int threads_total = __VERIFIER_nondet_int();
  assume_abort_if_not(threads_total >= 0);
  assume_abort_if_not(threads_total < 32); // can't have more threads than bits in mask

  pthread_t *tids = malloc(threads_total * sizeof(pthread_t));
  datas = malloc(threads_total * sizeof(int));

  // create threads
  for (int i = 0; i < threads_total; i++) {
    pthread_mutex_lock(&threads_mask_mutex);
    // find first 1 bit index
    int j = ffs(threads_mask) - 1; // NORACE
    // change j-th bit to 0
    threads_mask &= ~(1 << j); // NORACE
    pthread_mutex_unlock(&threads_mask_mutex);

    pthread_create(&tids[i], NULL, &thread, (void*)j); // may fail but doesn't matter
  }

  // join threads
  for (int i = 0; i < threads_total; i++) {
    pthread_join(tids[i], NULL);
  }

  free(tids);
  free(datas);

  return 0;
}
