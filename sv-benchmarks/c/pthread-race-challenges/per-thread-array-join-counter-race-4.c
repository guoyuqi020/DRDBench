// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2023 University of Tartu
//
// SPDX-License-Identifier: MIT

// PARAM: --set ana.activated[+] symb_locks
// Per-thread array index passed via argument.
// Thread pool joining via threads alive counter decremented based on thread array values.
// Extracted from smtprc.
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern int __VERIFIER_nondet_int();

int threads_total;
int threads_alive = 0;
pthread_mutex_t threads_alive_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t threads_alive_cond = PTHREAD_COND_INITIALIZER;

pthread_t *tids;
bool *datas;
pthread_mutex_t *datas_mutex;

void *thread(void *arg) {
  int i = (int)arg;
  pthread_mutex_lock(&datas_mutex[i]);
  datas[i] = true; // NORACE
  pthread_mutex_unlock(&datas_mutex[i]);
  return NULL;
}

void *cleaner(void *arg) {
  while (1) {
    for (int i = 0; i < threads_total; i++) {
      pthread_mutex_lock(&datas_mutex[i]);
      if (datas[i]) { // NORACE
        pthread_join(tids[i], NULL); // NORACE
        pthread_mutex_lock(&threads_alive_mutex);
        threads_alive--; // NORACE
        pthread_cond_signal(&threads_alive_cond);
        pthread_mutex_unlock(&threads_alive_mutex);
        datas[i] = false; // RACE!
      }
      pthread_mutex_unlock(&datas_mutex[i]);
    }
  }
  return NULL;
}

int main() {
  threads_total = __VERIFIER_nondet_int();
  assume_abort_if_not(threads_total >= 1);

  tids = malloc(threads_total * sizeof(pthread_t));
  datas = calloc(threads_total, sizeof(bool));
  datas_mutex = malloc(threads_total * sizeof(pthread_mutex_t));

  for (int i = 0; i < threads_total; i++)
    pthread_mutex_init(&datas_mutex[i], NULL);

  // create threads
  pthread_t cleaner_tid;
  pthread_create(&cleaner_tid, NULL, &cleaner, NULL);

  for (int i = 0; i < threads_total; i++) {
    pthread_create(&tids[i], NULL, &thread, (void*)i); // NORACE may fail but doesn't matter

    pthread_mutex_lock(&threads_alive_mutex);
    threads_alive++; // NORACE
    pthread_cond_signal(&threads_alive_cond);
    pthread_mutex_unlock(&threads_alive_mutex);
  }

  // wait for all threads to stop
  pthread_mutex_lock(&threads_alive_mutex);
  while (threads_alive) // NORACE
    pthread_cond_wait(&threads_alive_cond, &threads_alive_mutex);
  pthread_mutex_unlock(&threads_alive_mutex);

  free(tids);

  return datas[0]; // RACE! (with cleaner)
}
