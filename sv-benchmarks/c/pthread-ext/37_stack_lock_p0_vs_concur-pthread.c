extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

//original file: EBStack.java
//amino-cbbs\trunk\amino\java\src\main\java\org\amino\ds\lockfree
//push only

#include <pthread.h>

#define assume(e) assume_abort_if_not(e)
#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

#define MEMSIZE (2*32+1) //0 for "NULL"
int memory[MEMSIZE];
#define INDIR(cell,idx) memory[cell+idx]

int next_alloc_idx = 1;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int top = 0;

void __VERIFIER_atomic_index_malloc(int *curr_alloc_idx)
{
	if(next_alloc_idx+2-1 > MEMSIZE) *curr_alloc_idx = 0;
	else *curr_alloc_idx = next_alloc_idx, next_alloc_idx += 2;
}

#define isEmpty() (top == 0)

#define exit(r) assume(0)

inline void push(int d) {
	int oldTop = -1, newTop = -1;

	__VERIFIER_atomic_index_malloc(&newTop);
	if(newTop == 0)
		exit(-1);
	else{
		INDIR(newTop,0) = d;
		pthread_mutex_lock(&m);
		oldTop = top;
		INDIR(newTop,1) = oldTop;
		top = newTop; 
		pthread_mutex_unlock(&m);
	}
}

void* thr1(void* arg){
    while(1) {
        push(10); 
        pthread_mutex_lock(&m);
        assert(top != 0);
        pthread_mutex_unlock(&m);
    }

  return 0;
}

int main()
{
  pthread_t t;

	while(1) { pthread_create(&t, 0, thr1, 0); }
}

