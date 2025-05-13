/* Contributed by: Vladimír Štill, https://divine.fi.muni.cz
   Description: A test of the DIVINE fifo, buggy version.
*/

#define NODE_SIZE 2
#define INSERTS 7
#define BUG
#include <pthread.h>
#include <stdlib.h>
void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

#undef assert
#define assert( X ) (!(X) ? reach_error() : (void)0)

struct FifoNode_ {
    int *read;
    int buffer[ NODE_SIZE ];
    int *volatile write;
    struct FifoNode_ *next;
};

typedef struct FifoNode_ FifoNode;

FifoNode *fifo_node_init( FifoNode *self ) {
    self->read = self->write = self->buffer;
    self->next = 0;
    return self;
}

struct Fifo_ {
    FifoNode *head;
    FifoNode *volatile tail;
};

typedef struct Fifo_ Fifo;

_Bool fifo_empty( Fifo *self ) {
    return self->head == self->tail && self->head->read >= self->head->write;
}

Fifo *fifo_init( Fifo *self ) {
    self->head = self->tail = fifo_node_init( malloc( sizeof( FifoNode ) ) );
    assert( fifo_empty( self ) );
    return self;
}

void *fifo_destroy( Fifo *self ) {
    while ( self->head != self->tail ) {
        FifoNode *next = self->head->next;
        assert( next != 0 );
        free( self->head );
        self->head = next;
    }
    free( self->head );
    return self;
}

void fifo_push( Fifo *self, int x ) {
    FifoNode *t;
    if ( self->tail->write == self->tail->buffer + NODE_SIZE )
        t = fifo_node_init( malloc( sizeof( FifoNode ) ) );
    else
        t = self->tail;

    *t->write = x;
    ++t->write;

    if ( self->tail != t ) {
        self->tail->next = t;
        self->tail = t;
    }
}

int fifo_size( Fifo *self ) {
    int size = 0;
    FifoNode *n = self->head;
    do {
        size += n->write - n->read;
        n = n->next;
    } while ( n );
    return size;
}

void fifo_drop_head( Fifo *self ) {
    FifoNode *old = self->head;
    self->head = self->head->next;
    assert( !!self->head );
    free( old );
}

void fifo_pop( Fifo *self ) {
  again:
    assert( !fifo_empty( self ) );
    ++self->head->read;
    if ( self->head->read == self->head->buffer + NODE_SIZE ) {
#ifdef BUG
        if ( self->head->next != NULL )
#else
        if ( self->head != self->tail )
#endif
        {
            fifo_drop_head( self );
        }
    }
    // the following can happen when head->next is 0 even though head->read
    // has reached NodeSize, *and* no front() has been called in the meantime
#ifdef BUG
    if ( self->head != self->tail && self->head->read > self->head->buffer + NODE_SIZE )
#else
    if ( self->head->read > self->head->buffer + NODE_SIZE )
#endif
    {
        fifo_drop_head( self );
        goto again;
    }
}

int *fifo_front( Fifo *self, _Bool wait ) {
    while ( wait && fifo_empty( self ) ) ;
    assert( !!self->head );
    assert( !fifo_empty( self ) );
    // last pop could have left us with empty queue exactly at an
    // edge of a block, which leaves head->read == NodeSize
    if ( self->head->read == self->head->buffer + NODE_SIZE ) {
        fifo_drop_head( self );
    }
    return self->head->read;
}

///////////////////////////////

void *pusher( void *q_ ) {
    Fifo *q = q_;
    for ( int i = 0; i < INSERTS; ++i )
        fifo_push( q, 42 + i );
    return 0;
};



int main() {
    Fifo q;
    fifo_init( &q );
    pthread_t p;
    pthread_create( &p, 0, &pusher, &q );

    for ( int i = 0; i < INSERTS; ++i ) {
        int got = *fifo_front( &q, 1 );
        fifo_pop( &q );
        assert( got == 42 + i );
    }
    assert( fifo_empty( &q ) );
    pthread_join( p, 0 );
    assert( fifo_empty( &q ) );
    fifo_destroy( &q );

    return 0;
}
