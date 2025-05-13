// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2018 The Nidhugg project
// SPDX-FileCopyrightText: 2011-2020 The SV-Benchmarks community
// SPDX-FileCopyrightText: The ESBMC project
//
// SPDX-License-Identifier: Apache-2.0 AND GPL-3.0-or-later

#include <assert.h>

void reach_error() { assert(0); }

#include <stdlib.h>
#include <pthread.h>
int i, j;
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);
int p, q;
void *t1(void *arg) {
  for (p = 0; p < 10; p++) {
    __VERIFIER_atomic_begin();
    i = i + j;
    __VERIFIER_atomic_end();
  }
  return ((void *)0);
}
void *t2(void *arg) {
  for (q = 0; q < 10; q++) {
    __VERIFIER_atomic_begin();
    j = j + i;
    __VERIFIER_atomic_end();
  }
  return ((void *)0);
}
int cur = 1, prev = 0, next = 0;
int x;
int fib() {
  for (x = 0; x < 22; x++) {
    next = prev + cur;
    prev = cur;
    cur = next;
  }
  return prev;
}
int main(int argc, char **argv) {
  pthread_t id1, id2;
  __VERIFIER_atomic_begin();
  i = 1;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  j = 1;
  __VERIFIER_atomic_end();
  pthread_create(&id1, ((void *)0), t1, ((void *)0));
  pthread_create(&id2, ((void *)0), t2, ((void *)0));
  int correct = fib();
  
  if(i < correct && j < correct) ;
  else ERROR: {reach_error();abort();}
  
  return 0;
}
