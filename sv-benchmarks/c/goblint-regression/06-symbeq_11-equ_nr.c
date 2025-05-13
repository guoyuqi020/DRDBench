// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2005-2021 University of Tartu & Technische Universität München
//
// SPDX-License-Identifier: MIT

extern int __VERIFIER_nondet_int();

#include<pthread.h>
#include<stdlib.h>
#include<limits.h>

struct q { int x; int y; };
struct s {
  int datum;
  struct q inside;
  pthread_mutex_t mutex;
} A, B;

void *t_fun(void *arg) {
  pthread_mutex_lock(&A.mutex);
  A.datum = 5; // NORACE
  pthread_mutex_unlock(&A.mutex);
  return NULL;
}

int main () {
  pthread_mutex_init(&A.mutex, NULL);
  pthread_mutex_init(&B.mutex, NULL);

  int x = __VERIFIER_nondet_int();
  if (x == INT_MAX) {
    return 0;
  }
  pthread_t id;

  // struct s *s = malloc(sizeof(struct s));
  struct s *s;
  //struct q *q;
  int *d;

  pthread_mutex_t *m;

  if (x) {
	  s = &A;
	  x++;
  } else {
	  s = &B;
	  x++;
  }

  //q = &s->inside;
  m = &s->mutex;
  d = &s->datum;

  pthread_create(&id,NULL,t_fun,NULL);

  pthread_mutex_lock(m);
  *d = 8; // NORACE
  pthread_mutex_unlock(m);

  return 0;
}
