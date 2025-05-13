// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2016 SCTBench Project
// SPDX-FileCopyrightText: The ESBMC Project
//
// SPDX-License-Identifier: Apache-2.0
#define N 30
#include <pthread.h>
#include <assert.h>

#define CHECK 1
#define SET (N-1)
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

static int a, b;
int i;

static void *setThread(void *param) {
  __VERIFIER_atomic_begin();
  a = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  b = -1;
  __VERIFIER_atomic_end();
  // atomic_store(a, 1);
  // atomic_store(b, -1);

  return NULL;
}

static void *checkThread(void *param) {
  assert((a == 0 && b == 0) || (a == 1 && b == -1));

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t setPool[SET];
  pthread_t checkPool[CHECK];

  for (i = 0; i < SET; i++)
    pthread_create(&setPool[i], NULL, &setThread, NULL);
  for (i = 0; i < CHECK; i++)
    pthread_create(&checkPool[i], NULL, &checkThread, NULL);

  for (i = 0; i < SET; i++)
    pthread_join(setPool[i], NULL);
  for (i = 0; i < CHECK; i++)
    pthread_join(checkPool[i], NULL);
}
