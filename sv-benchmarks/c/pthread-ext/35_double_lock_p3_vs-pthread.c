extern int __VERIFIER_nondet_int(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

#include <pthread.h>

int count = 0;

#define assert_nl(e) { if(!(e)) { goto ERROR; } }
#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

pthread_mutex_t mutexa = PTHREAD_MUTEX_INITIALIZER;
inline void my_thread1()
{
  pthread_mutex_lock(&mutexa);
  count++;
  count--;
  pthread_mutex_unlock(&mutexa);

  pthread_mutex_lock(&mutexa);
  count--;
  count++;
  pthread_mutex_unlock(&mutexa);

  return;
}

void* thr1(void* arg)
{
  while(1)
  {
    pthread_mutex_lock(&mutexa);
    assert(count >= -1);
    pthread_mutex_unlock(&mutexa);
  }
  return 0;
}

void* thr2(void* arg)
{
  if(__VERIFIER_nondet_int())
    my_thread1();
  //else
    //my_thread2();
  return 0;
}

int main(void)
{
  pthread_t t;

  pthread_create(&t, 0, thr1, 0);
  while(1)
  {
      pthread_create(&t, 0, thr2, 0);
  }
}

