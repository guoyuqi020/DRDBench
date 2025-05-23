// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2023 University of Tartu
//
// SPDX-License-Identifier: MIT

// Thread pool joining via threads alive counter incremented inside of thread.
// Extracted from concrat/C-Thread-Pool.
#include <stdbool.h>
#include <pthread.h>
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern int __VERIFIER_nondet_int();

int threads_alive = 0;

bool keep_alive = true;
pthread_mutex_t keep_alive_mutex = PTHREAD_MUTEX_INITIALIZER;

int data = 0;
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread(void *arg) {
  threads_alive++; // RACE!

  pthread_mutex_lock(&keep_alive_mutex);
  while (keep_alive) { // NORACE
    pthread_mutex_unlock(&keep_alive_mutex);

    pthread_mutex_lock(&data_mutex);
    data = __VERIFIER_nondet_int(); // RACE!
    pthread_mutex_unlock(&data_mutex);

    pthread_mutex_lock(&keep_alive_mutex);
  }
  pthread_mutex_unlock(&keep_alive_mutex);

  threads_alive--; // RACE!
  return NULL;
}

int main() {
  int threads_total = __VERIFIER_nondet_int();
  assume_abort_if_not(threads_total >= 0);

  // create threads
  for (int i = 0; i < threads_total; i++) {
    pthread_t tid;
    pthread_create(&tid, NULL, &thread, NULL); // may fail but doesn't matter
    pthread_detach(tid);
  }

  // wait for all threads to come alive
  while (threads_alive != threads_total); // RACE!

  // stop threads
  pthread_mutex_lock(&keep_alive_mutex);
  keep_alive = false; // NORACE
  pthread_mutex_unlock(&keep_alive_mutex);

  // wait for all threads to stop
  while (threads_alive); // RACE!

  return data; // RACE! (all threads may not have stopped due to lost increments)
}
