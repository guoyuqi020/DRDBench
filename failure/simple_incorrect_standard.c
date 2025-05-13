#include <assert.h>
#include <pthread.h>
pthread_mutex_t flag1, flag2;
int x;
void *thr1(void *_)
{
    pthread_mutex_lock(&flag1);
    pthread_mutex_lock(&flag2);
    x = 0;
    return 0;
}
void *thr2(void *_)
{
    pthread_mutex_lock(&flag2);
    pthread_mutex_lock(&flag1);
    x = 1;
    return 0;
}
int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, 0, thr1, 0);
    pthread_create(&t2, 0, thr2, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    return 0;
}