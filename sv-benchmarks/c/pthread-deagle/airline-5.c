// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2018 The Nidhugg project
// SPDX-FileCopyrightText: 2017 Texas A&M University
//
// SPDX-License-Identifier: MIT AND GPL-3.0-or-later

/*
 * This benchmark is part of SWSC
 * Get inspiration from the Ariline example in Tables 1 and 2 in the PLDI 2015
 * paper: https://dl.acm.org/doi/pdf/10.1145/2737924.2737975
 */

#define N 5
#include <assert.h>
#include <pthread.h>
#include <stdint.h>
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

#define NumOfExtra (((N / 10) == 0) ? 1 : (N / 10))
#define MaximumCapacity (N - NumOfExtra)

// shared variables
int numberOfSeatsSold;
int stopSales;
int numOfTickets;

void *salethread(void *arg) {
  if (!stopSales) {
    int _numberOfSeatsSold = numberOfSeatsSold;
    if (_numberOfSeatsSold >= MaximumCapacity) {
      __VERIFIER_atomic_begin();
      stopSales = 1;
      __VERIFIER_atomic_end();
      // atomic_store_explicit(&stopSales, 1, memory_order_seq_cst);
    } else {
      __VERIFIER_atomic_begin();
      numberOfSeatsSold = _numberOfSeatsSold + 1;
      __VERIFIER_atomic_end();
      // atomic_store_explicit(&numberOfSeatsSold, _numberOfSeatsSold+1,
      // memory_order_seq_cst);
    }
  }

  return NULL;
}

int main(int argc, char **argv) {
  pthread_t salethreads[N];

  // atomic_init(&numOfTickets, N);
  // atomic_init(&numberOfSeatsSold, 0);
  // atomic_init(&stopSales, 0);
  __VERIFIER_atomic_begin();
  numOfTickets = N;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  numberOfSeatsSold = 0;
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_begin();
  stopSales = 0;
  __VERIFIER_atomic_end();

  for (int i = 0; i < N; i++) {
    pthread_create(&salethreads[i], 0, salethread, NULL);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(salethreads[i], 0);
  }

  int _numberOfSeatsSold = numberOfSeatsSold;
  assert(_numberOfSeatsSold <= MaximumCapacity); // not too many tickets sold
  // assert(_numberOfSeatsSold >= MaximumCapacity);	// not too few tickets
  // sold

  return 0;
}
