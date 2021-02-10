#ifndef mulle__pointerfifo64_h__
#define mulle__pointerfifo64_h__

#include "include.h"



/*
 * FIFO: single consumer thrad / single producer thread only
 *       Fixed size for simplicity of implementation
 */

struct mulle__pointerfifo64
{
   mulle_atomic_pointer_t   n;        
   unsigned int             write;    // only accessed by producer
   unsigned int             read;     // only accessed by consumer
   mulle_atomic_pointer_t   storage[ 64];
};


static inline void   _mulle__pointerfifo64_init( struct mulle__pointerfifo64 *p)
{
   p->write = 0;
   p->read  = 0;
   _mulle_atomic_pointer_nonatomic_write( &p->n, 0);
}


static inline void   _mulle__pointerfifo64_done( struct mulle__pointerfifo64 *p)
{
}


static inline unsigned int   _mulle__pointerfifo64_get_count( struct mulle__pointerfifo64 *p)
{
   return( (unsigned int) (uintptr_t) _mulle_atomic_pointer_read( &p->n));
}



static inline void   *_mulle__pointerfifo64_read( struct mulle__pointerfifo64 *p)
{
   void   *pointer;

   if( ! _mulle__pointerfifo64_get_count( p))
      return( NULL);

   pointer  = _mulle_atomic_pointer_read( &p->storage[ p->read]);
   p->read  = (p->read + 1) % 64;
   _mulle_atomic_pointer_decrement( &p->n);

   return( pointer);
}


static inline int   _mulle__pointerfifo64_write( struct mulle__pointerfifo64 *p,
                                                 void *pointer)
{
   if( _mulle__pointerfifo64_get_count( p) == 64)
      return( -1);

   _mulle_atomic_pointer_write( &p->storage[ p->write], pointer);
   p->write = (p->write + 1) % 64;
   _mulle_atomic_pointer_increment( &p->n);

   return( 0);
}

#endif


