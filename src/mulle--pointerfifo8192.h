// Generated file. Don't edit. Edit mulle--pointerfifo64.h
// then run ../bin/create-fifo-sources

//
//  mulle--pointerfifo8192.h
//  mulle-fifo
//
//  Created by Nat! on 10.02.2021
//  Copyright © 2021 Nat! for Mulle kybernetiK.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
#ifndef mulle__pointerfifo8192_h__
#define mulle__pointerfifo8192_h__

#include "include.h"

#include <assert.h>


/*
 * FIFO: single consumer thread / single producer thread only
 *       Fixed size for simplicity of implementation. If you point to 
 *       memory from the queue, be sure that you have issued a memory
 *       barrier call after setting values into reused memory.
 */

struct mulle__pointerfifo8192
{
   mulle_atomic_pointer_t   n;        
   unsigned int             write;    // only accessed by producer
   unsigned int             read;     // only accessed by consumer
   mulle_atomic_pointer_t   storage[ 8192];
};


static inline void   _mulle__pointerfifo8192_init( struct mulle__pointerfifo8192 *p)
{
   p->write = 0;
   p->read  = 0;
   _mulle_atomic_pointer_nonatomic_write( &p->n, 0);
}


static inline void   _mulle__pointerfifo8192_done( struct mulle__pointerfifo8192 *p)
{
   MULLE_C_UNUSED( p);
}


static inline unsigned int   _mulle__pointerfifo8192_get_count( struct mulle__pointerfifo8192 *p)
{
   return( (unsigned int) (uintptr_t) _mulle_atomic_pointer_read( &p->n));
}



static inline void   *_mulle__pointerfifo8192_read( struct mulle__pointerfifo8192 *p)
{
   void   *pointer;

   if( ! _mulle__pointerfifo8192_get_count( p))
      return( NULL);

   pointer  = _mulle_atomic_pointer_read( &p->storage[ p->read]);
   p->read  = (p->read + 1) % 8192;
   _mulle_atomic_pointer_decrement( &p->n);

   return( pointer);
}


static inline void   *_mulle__pointerfifo8192_read_barrier( struct mulle__pointerfifo8192 *p)
{
   void   *pointer;

   if( ! _mulle__pointerfifo8192_get_count( p))
      return( NULL);

   // get fresh look, now we don't need and atomic pointer read for the
   // storage and the contents of whats pointed to with pointer is in sync
   // with what was written
   mulle_atomic_memory_barrier();

   pointer  = _mulle_atomic_pointer_nonatomic_read( &p->storage[ p->read]);
   p->read  = (p->read + 1) % 8192;
   _mulle_atomic_pointer_decrement( &p->n);

   return( pointer);
}


static inline int   _mulle__pointerfifo8192_write( struct mulle__pointerfifo8192 *p,
                                                 void *pointer)
{
   assert( pointer != NULL);

   if( _mulle__pointerfifo8192_get_count( p) == 8192)
      return( -1);

   _mulle_atomic_pointer_write( &p->storage[ p->write], pointer);
   p->write = (p->write + 1) % 8192;
   _mulle_atomic_pointer_increment( &p->n);

   return( 0);
}

#endif


