// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2018 The Nidhugg project
//
// SPDX-License-Identifier: GPL-3.0-or-later
#define N 10
#include <assert.h>
#include <pthread.h>
#include <stdint.h>

extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

intptr_t x;

static void *thread(void *arg) {
  intptr_t thread = (intptr_t)arg;
  __VERIFIER_atomic_begin();
  x = thread;
  __VERIFIER_atomic_end();
  // atomic_store(&x, thread);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t[N + 1];
  __VERIFIER_atomic_begin();
  x = 0;
  __VERIFIER_atomic_end();
  // atomic_init(&x, 0);
  for (intptr_t i = 1; i <= N; i++)
    pthread_create(t + i, 0, thread, (void *)i);
  assert(x < N + 1);
  for (intptr_t i = 1; i <= N; i++)
    pthread_join(t[i], 0);
  return 0;
}
