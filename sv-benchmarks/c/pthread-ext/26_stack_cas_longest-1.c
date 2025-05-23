extern int __VERIFIER_nondet_int(void);
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern void __VERIFIER_atomic_begin(void);
extern void __VERIFIER_atomic_end(void);
//original file: EBStack.java
//amino-cbbs\trunk\amino\java\src\main\java\org\amino\ds\lockfree
//push only

#include <pthread.h>

#define assume(e) assume_abort_if_not(e)
#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();} (void)0; } }

void __VERIFIER_atomic_acquire(int * m)
{
	assume(*m==0);
	*m = 1;
}

void __VERIFIER_atomic_release(int * m)
{
	assume(*m==1);
	*m = 0;
}

void __VERIFIER_atomic_CAS(
  int *v,
  int e,
  int u,
  int *r)
{
	if(*v == e)
	{
		*v = u, *r = 1;
	}
	else
	{
		*r = 0;
	}
}

#define MEMSIZE (2*960+1) //0 for "NULL"
int memory[MEMSIZE];
#define INDIR(cell,idx) memory[cell+idx]

int next_alloc_idx = 1;
int m = 0;
int top;

inline int index_malloc(){
	int curr_alloc_idx = -1;

	__VERIFIER_atomic_acquire(&m);
	if(next_alloc_idx+2-1 > MEMSIZE){
		__VERIFIER_atomic_release(&m);
		curr_alloc_idx = 0;
	}else{
		curr_alloc_idx = next_alloc_idx;
		next_alloc_idx += 2;
		__VERIFIER_atomic_release(&m);
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
	int oldTop = -1, newTop = -1, casret = -1;

	newTop = index_malloc();
	if(newTop == 0){
		return 0;
	}else{
		INDIR(newTop,0) = d;
		while (1) {
			__VERIFIER_atomic_begin();
			oldTop = top;
			__VERIFIER_atomic_end();
			INDIR(newTop,1) = oldTop;
			__VERIFIER_atomic_CAS(&top,oldTop,newTop,&casret);
			if(casret==1){
				return 1;
			}

		}
	}
}

void __VERIFIER_atomic_assert(int r)
{
		assert(!(!r || !isEmpty()));
}

inline void push_loop(){
	int r = -1;
	int arg = __VERIFIER_nondet_int();
	while(1){
		r = push(arg);
    __VERIFIER_atomic_assert(r);
	}
}

int m2 = 0;
int state = 0;
void* thr1(void* arg)
{
	__VERIFIER_atomic_acquire(&m2);
	switch(state)
	{
	case 0: 
		EBStack_init();
		state = 1;
		//fall-through
	case 1: 
		__VERIFIER_atomic_release(&m2);
		
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

