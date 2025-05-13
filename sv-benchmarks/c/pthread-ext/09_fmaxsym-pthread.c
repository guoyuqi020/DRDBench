extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern int __VERIFIER_nondet_int();

#include <pthread.h>

#define assume(e) assume_abort_if_not(e)
#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

#define WORKPERTHREAD 2
#define THREADSMAX 3
volatile int max = 0x80000000;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int storage[WORKPERTHREAD*THREADSMAX];

inline void findMax(int offset)
{
	int i;
	int e;

	for(i = offset; i < offset+WORKPERTHREAD; i++) {
		e = storage[i];
		
		pthread_mutex_lock(&m);
		{
			if(e > max) {
				max = e;
			}
		}
		pthread_mutex_unlock(&m);
        pthread_mutex_lock(&m);
		assert(e <= max);
		pthread_mutex_unlock(&m);
	}
}

void* thr1(void* arg) {
  int offset=__VERIFIER_nondet_int();

	assume(offset % WORKPERTHREAD == 0 && offset >= 0 && offset < WORKPERTHREAD*THREADSMAX);
	//assume(offset < WORKPERTHREAD && offset >= 0 && offset < WORKPERTHREAD*THREADSMAX);

	findMax(offset);

  return 0;
}

int main(){
  for (int i = 0; i < WORKPERTHREAD*THREADSMAX; i++)
    storage[i] = __VERIFIER_nondet_int();

  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

