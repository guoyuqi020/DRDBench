extern int __VERIFIER_nondet_int(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);

//original file: EBStack.java
//amino-cbbs\trunk\amino\java\src\main\java\org\amino\ds\lockfree
//push only

#include <pthread.h>

#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

#define MEMSIZE (2*32+1) //0 for "NULL"
int memory[MEMSIZE];
#define INDIR(cell,idx) memory[cell+idx]

int next_alloc_idx = 1;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int top;

inline int index_malloc(){
	int curr_alloc_idx = -1;

	pthread_mutex_lock(&m);
	if(next_alloc_idx+2-1 > MEMSIZE){
		pthread_mutex_unlock(&m);
		curr_alloc_idx = 0;
	}else{
		curr_alloc_idx = next_alloc_idx;
		next_alloc_idx += 2;
		pthread_mutex_unlock(&m);
	}

	return curr_alloc_idx;
}

inline void EBStack_init(){
	top = 0;
}

inline int isEmpty() {
	if(top == 0)
		return 1;
	else
		return 0;
}

inline int push(int d) {
	int oldTop = -1, newTop = -1;

	newTop = index_malloc();
	if(newTop == 0){
		return 0;
	}else{
		INDIR(newTop,0) = d;

		pthread_mutex_lock(&m);
		oldTop = top;
		INDIR(newTop,1) = oldTop;
		__VERIFIER_atomic_begin();
		top = newTop; 
		__VERIFIER_atomic_end();
		pthread_mutex_unlock(&m);
		return 1;
	}
}

inline void init(){
	EBStack_init();
}

void __VERIFIER_atomic_assert(int r)
{
		assert(!r || !isEmpty());
}

inline void push_loop(){
	int r = -1;
	int arg = __VERIFIER_nondet_int();
	while(1){
		r = push(arg);
    __VERIFIER_atomic_assert(r);
	}
}

pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
int state = 0;
void* thr1(void* arg)
{
	pthread_mutex_lock(&m2);
	switch(state)
	{
	case 0: 
		EBStack_init();
		state = 1;
		//fall-through
	case 1: 
		pthread_mutex_unlock(&m2);
		
		push_loop();
		break;
	}

  return 0;
}

int main()
{
  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

