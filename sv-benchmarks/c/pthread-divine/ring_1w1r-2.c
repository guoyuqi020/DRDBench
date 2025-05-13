/* Contributed by: Vladimír Štill, https://divine.fi.muni.cz
   Description: A test of bounded lock-free queue.
*/


#include <pthread.h>
#include <string.h>
void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

#undef assert
#define assert( X ) (!(X) ? reach_error() : (void)0)

#define SIZE 4
#define CNT 8

typedef struct _ring {
    volatile long reader;
    long q[ SIZE ];
    volatile long writer;
} Ring;

void ring_enqueue( Ring *r, long x ) {
    while ( (r->writer + 1) % SIZE == r->reader ); // full; need to wait
    r->q[ r->writer ] = x;
    r->writer = (r->writer + 1) % SIZE;
}

long ring_dequeue( Ring *r ) {
    long x = r->q[ r->reader ];
    r->reader = (r->reader + 1) % SIZE;
    return x;
}

_Bool ring_empty( Ring *r ) {
    return r->reader == r->writer;
}

void ring_init( Ring *r ) {
    r->reader = r->writer = 0;
}

void *reader_fn( void *arg ) {
    Ring *r = arg;
    long val = 0, last = 0, i = 0;
    while ( i < CNT ) {
        if ( ring_empty( r ) )
            continue;
        val = ring_dequeue( r );
        assert( val == last + 1 );
        last = val;
        ++i;
    }
    assert( last == CNT );
    assert( ring_empty( r ) );
    return 0;
}

void *writer_fn( void *arg ) {
    Ring *r = arg;
    for ( long i = 0; i < CNT; ++i ) {
        ring_enqueue( r, i + 1 );
    }
    return 0;
}


int main() {
    pthread_t reader;
    Ring r;
    ring_init( &r );
    pthread_create( &reader, NULL, &reader_fn, &r );
    writer_fn( &r );
    pthread_join( reader, NULL );
}
