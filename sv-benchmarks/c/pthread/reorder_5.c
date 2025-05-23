// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2011-2020 The SV-Benchmarks community
// SPDX-FileCopyrightText: The ESBMC project
//
// SPDX-License-Identifier: Apache-2.0

extern void abort(void);
extern void __assert_fail(const char *, const char *, unsigned int, const char *) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
void reach_error() { __assert_fail("0", "reorder_5.c", 3, "reach_error"); }
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define LIMIT 100000

static int iSet = 4;
static int iCheck = 1;

static int a = 0;
static int b = 0;

void __ESBMC_yield();

void *setThread(void *param);
void *checkThread(void *param);
void set();
int check();

int main(int argc, char *argv[]) {
    int i, err;

    if (argc != 1) {
        if (argc != 3) {
            fprintf(stderr, "./reorder <param1> <param2>\n");
            exit(-1);
        } else {
            sscanf(argv[1], "%d", &iSet);
            sscanf(argv[2], "%d", &iCheck);
        }
    }
    
    if (iSet > LIMIT || iCheck > LIMIT) {
      exit(-1);
    }

    pthread_t setPool[iSet];
    pthread_t checkPool[iCheck];

    for (i = 0; i < iSet; i++) {
        if (0 != (err = pthread_create(&setPool[i], ((void *)0), &setThread, ((void *)0)))) {
            fprintf(stderr, "Error [%d] found creating set thread.\n", err);
            exit(-1);
        }
    }

    for (i = 0; i < iCheck; i++) {
        if (0 != (err = pthread_create(&checkPool[i], ((void *)0), &checkThread,
                                       ((void *)0)))) {
            fprintf(stderr, "Error [%d] found creating check thread.\n", err);
            exit(-1);
        }
    }

    for (i = 0; i < iSet; i++) {
        if (0 != (err = pthread_join(setPool[i], ((void *)0)))) {
            fprintf(stderr, "pthread join error: %d\n", err);
            exit(-1);
        }
    }

    for (i = 0; i < iCheck; i++) {
        if (0 != (err = pthread_join(checkPool[i], ((void *)0)))) {
            fprintf(stderr, "pthread join error: %d\n", err);
            exit(-1);
        }
    }

    return 0;
}

void *setThread(void *param) {
    __VERIFIER_atomic_begin();
    a = 1;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    b = -1;
    __VERIFIER_atomic_end();

    return ((void *)0);
}

void *checkThread(void *param) {
    __VERIFIER_atomic_begin();
    int la = a;
    __VERIFIER_atomic_end();
    __VERIFIER_atomic_begin();
    int lb = b;
    __VERIFIER_atomic_end();
    if (! ((la == 0 && lb == 0) || (la == 1 && lb == -1))) {
        fprintf(stderr, "Bug found!\n");
        ERROR: {reach_error();abort();}
    }

    return ((void *)0);
}
