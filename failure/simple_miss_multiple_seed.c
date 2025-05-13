#include <assert.h>
#include <pthread.h>
int m = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void atomic_acquire()
{
    pthread_mutex_lock(&mutex);
    while (m != 0)
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    m = 1;
    pthread_mutex_unlock(&mutex);
}
void atomic_release()
{
    pthread_mutex_lock(&mutex);
    while (m != 1)
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    m = 0;
    pthread_mutex_unlock(&mutex);
}
inline int calculateNext(int s2)
{
    int cnex;
    do
        cnex = rand();
    while (cnex == s2 || cnex == 0);
    return cnex;
}
int seed = 1;
inline int PseudoRandomUsingAtomic_nextInt()
{
    int read, nexts;
    assert(seed != 0);
    atomic_acquire();
    read = seed;
    nexts = calculateNext(read);
    seed = nexts;
    atomic_release();
    return 0;
}
void *thr1(void *arg)
{
    PseudoRandomUsingAtomic_nextInt();
    return 0;
}
int main()
{
    pthread_t t;
    while (1)
    {
        pthread_create(&t, 0, thr1, 0);
    }
}