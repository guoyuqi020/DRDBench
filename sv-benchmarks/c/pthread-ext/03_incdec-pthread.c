extern int __VERIFIER_nondet_int(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

//http://www.ibm.com/developerworks/java/library/j-jtp04186/index.html
//Listing 2. A counter using locks

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

#define atomic_assert(e) {pthread_mutex_lock(&m);assert(e);pthread_mutex_unlock(&m);}

volatile unsigned value = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

/*helpers for the property*/
volatile unsigned inc_flag = 0;
volatile unsigned dec_flag = 0;

inline unsigned inc() {
	unsigned inc_v = 0;

	pthread_mutex_lock(&m);
	if(value == 0u-1) {
		pthread_mutex_unlock(&m);
		return 0;
	}else{
		inc_v = value;
		inc_flag = 1, value = inc_v + 1; /*set flag, then update*/
		pthread_mutex_unlock(&m);

		atomic_assert(dec_flag || value > inc_v);

		return inc_v + 1;
	}
}

inline unsigned dec() {
	unsigned dec_v;

	pthread_mutex_lock(&m);
	if(value == 0) {
		pthread_mutex_unlock(&m);

		return 0u-1; /*decrement failed, return max*/
	}else{
		dec_v = value;
		dec_flag = 1, value = dec_v - 1; /*set flag, then update*/
		pthread_mutex_unlock(&m);

		atomic_assert(inc_flag || value < dec_v);

		return dec_v - 1;
	}
}

void* thr1(void* arg){
	int r = __VERIFIER_nondet_int();

	if(r){ inc(); }
	else{ dec(); }

  return 0;
}

int main(){
  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

