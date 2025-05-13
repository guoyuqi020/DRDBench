extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

//http://www.ibm.com/developerworks/java/library/j-jtp04186/index.html
//A counter using locks

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

volatile unsigned value;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void * thr1(void* arg) {
	unsigned v = 0;

	pthread_mutex_lock(&m);
	if(value == 0u-1) {
		pthread_mutex_unlock(&m);

		return 0;
	}else{

		v = value;
		__VERIFIER_atomic_begin(); value = v + 1; __VERIFIER_atomic_end(); // atomics added to prevent data race
		pthread_mutex_unlock(&m);

        __VERIFIER_atomic_begin();
        assert(value > v);
        __VERIFIER_atomic_end();

		return 0;
	}
}

int main(){
  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

