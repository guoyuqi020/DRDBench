#include <assert.h>
#include <pthread.h>
int flag1 = 0, flag2 = 0;
int turn;
int x;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *thr1(void *_)
{
    pthread_mutex_lock(&mutex);
    flag1 = 1;
    while (flag2 == 1)
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
    x = 0; // no race, protected by flag1 and flag2
    return 0;
}
void *thr2(void *_)
{
    pthread_mutex_lock(&mutex);
    flag2 = 1;
    while (flag1 == 1)
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
    x = 1; // no race, protected by flag1 and flag2
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