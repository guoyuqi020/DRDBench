/* Contributed by: Vladimír Štill, https://divine.fi.muni.cz
   Description: A test case for pthread TLS.
*/

#include <pthread.h>
void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

#undef assert
#define assert( X ) (!(X) ? reach_error() : (void)0)

void *worker( void *k ) {
    pthread_key_t *key = k;
    long val = (long)pthread_getspecific( *key );
    assert( val == 0 );

    int r = pthread_setspecific( *key, (void *)42 );
    assert( r == 0 );

    val = (long)pthread_getspecific( *key );
    assert( val == 42 );

    return 0;
}

int main() {
    pthread_key_t key;
    int r = pthread_key_create( &key, NULL );
    assert( r == 0 );
    pthread_t tid;

    long val = (long)pthread_getspecific( key );
    assert( val == 0 );

    pthread_create( &tid, NULL, worker, &key );

    val = (long)pthread_getspecific( key );
    assert( val == 0 );

    r = pthread_setspecific( key, (void *)16 );
    assert( r == 0 );

    val = (long)pthread_getspecific( key );
    assert( val == 16 );

    pthread_join( tid, NULL );
    val = (long)pthread_getspecific( key );
    assert( val == 16 );

}
