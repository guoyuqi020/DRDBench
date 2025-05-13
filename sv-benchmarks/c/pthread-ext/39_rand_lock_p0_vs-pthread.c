extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

//http://www.ibm.com/developerworks/java/library/j-jtp11234/
//Listing 5. Implementing a thread-safe PRNG with synchronization and atomic variables

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

#define min(x,y) ((y>=x)?(x):(y))

inline int calculateNext(int s2){ 
	int cnex;
	do cnex = __VERIFIER_nondet_int();
	while(cnex == s2 || cnex == 0);
	return cnex;
}

int seed = 1; 

#define NUM 10

inline int PseudoRandomUsingAtomic_nextInt() {
	int read, nexts, nextInt_return;

    __VERIFIER_atomic_begin();
    assert(seed != 0);
    __VERIFIER_atomic_end();

	pthread_mutex_lock(&m);
	read = seed;
	nexts = calculateNext(read);
    __VERIFIER_atomic_begin();
	seed = nexts;
    __VERIFIER_atomic_end();
	pthread_mutex_unlock(&m);
	nextInt_return = min(nexts,NUM);
	return nextInt_return;
}

void* thr1(void* arg){
  PseudoRandomUsingAtomic_nextInt();

  return 0;
}

int main()
{
  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

