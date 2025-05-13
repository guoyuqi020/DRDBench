// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

#include <assert.h>
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}


extern int __VERIFIER_nondet_int();

#include <pthread.h>

int plus(int a, int b);

int g = 0;
int h = 0;
int i = 0;
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER; // h <= g
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER; // h == g
pthread_mutex_t C = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand
  int z = __VERIFIER_nondet_int(); //rand
  if (x < 1000) { // avoid overflow
    pthread_mutex_lock(&C);
    pthread_mutex_lock(&A);
    x = g;
    y = h;
    __VERIFIER_assert(y <= x);
    pthread_mutex_lock(&B);
    __VERIFIER_assert(x == y);
    pthread_mutex_unlock(&B);
    i = plus(x, 31);
    z = i;
    __VERIFIER_assert(z >= x);
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&C);
  }
  return NULL;
}

int main(void) {
  int x = __VERIFIER_nondet_int(); //rand
  if (x > -1000) { // avoid underflow
    pthread_t id;
    pthread_create(&id, NULL, t_fun, NULL);

    pthread_mutex_lock(&B);
    pthread_mutex_lock(&A);
    i = 11;
    g = x;
    h = plus(x, - 17);
    pthread_mutex_unlock(&A);
    pthread_mutex_lock(&A);
    h = x;
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&B);
    pthread_mutex_lock(&C);
    i = 3;
    pthread_mutex_unlock(&C);
  }
  return 0;
}

int plus(int a, int b) {
  assume_abort_if_not(b >= 0 || a >= -2147483648 - b);
  assume_abort_if_not(b <= 0 || a <= 2147483647 - b);
  return a + b;
}
