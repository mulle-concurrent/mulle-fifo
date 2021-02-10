#ifndef mulle__pointerfifo_h__
#define mulle__pointerfifo_h__

#include "include.h"


/*
 * FIFO: single consumer thrad / single producer thread only
 *       Non growing but size can be configured at init time.
 */
struct mulle__pointerfifo
{
   mulle_atomic_pointer_t   n;        
   unsigned int             write;    // only accessed by producer
   unsigned int             read;     // only accessed by consumer
   unsigned int             size;    // read only after init
   struct mulle_allocator   *allocator;
   mulle_atomic_pointer_t   *storage;
};


static inline void   _mulle__pointerfifo_init( struct mulle__pointerfifo *p, 
                                               unsigned int size,
                                               struct mulle_allocator *allocator)
{
   assert( size >= 2);

   p->write     = 0;
   p->read      = 0;
   p->size      = size;
   _mulle_atomic_pointer_nonatomic_write( &p->n, 0);
   p->allocator = allocator;
   p->storage   = mulle_allocator_malloc( allocator, size * sizeof( mulle_atomic_pointer_t));
}


static inline void   _mulle__pointerfifo_done( struct mulle__pointerfifo *p)
{
   mulle_allocator_free( p->allocator, p->storage);
}


static inline unsigned int   _mulle__pointerfifo_get_count( struct mulle__pointerfifo *p)
{
   return( (unsigned int) (uintptr_t) _mulle_atomic_pointer_read( &p->n));
}



static inline void   *_mulle__pointerfifo_read( struct mulle__pointerfifo *p)
{
   void   *pointer;

   if( ! _mulle__pointerfifo_get_count( p))
      return( NULL);

   pointer  = _mulle_atomic_pointer_read( &p->storage[ p->read]);
   p->read  = (p->read + 1) % p->size;
   _mulle_atomic_pointer_decrement( &p->n);

   return( pointer);
}


static inline int   _mulle__pointerfifo_write( struct mulle__pointerfifo *p,
                                                 void *pointer)
{
   if( _mulle__pointerfifo_get_count( p) == p->size)
      return( -1);

   _mulle_atomic_pointer_write( &p->storage[ p->write], pointer);
   p->write = (p->write + 1) % p->size;
   _mulle_atomic_pointer_increment( &p->n);

   return( 0);
}

#endif


