/* Contributed by: Vladimír Štill, https://divine.fi.muni.cz
   Description: A test case for pthread TLS. This test demonstartes that
                destructors are called.
*/

#include <pthread.h>
void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

#undef assert
#define assert( X ) (!(X) ? reach_error() : (void)0)

void dtor( void *v ) {
    long val = (long)v;
    assert( val != 42 ); // triggered by destructor of workers's version of TLS
}

void *worker( void *k ) {
    pthread_key_t *key = k;

    int r = pthread_setspecific( *key, (void *)42 );
    assert( r == 0 );
    return 0;
}

int main() {
    pthread_key_t key;
    int r = pthread_key_create( &key, &dtor );
    assert( r == 0 );

    pthread_t tid;
    pthread_create( &tid, NULL, worker, &key );

    r = pthread_setspecific( key, (void *)16 );
    assert( r == 0 );

    pthread_join( tid, NULL );
}
