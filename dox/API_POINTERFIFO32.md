# mulle__pointerfifo32

`mulle__pointerfifo32` is one of the fixed-size pointer FIFOs. The available
sizes are 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 and 8192
pointers; replace the `32` in the type and function names with the desired
size (e.g. `struct mulle__pointerfifo64`, `_mulle__pointerfifo64_write`).
The storage is part of the struct, so a fixed FIFO needs no allocator and
can live on the stack or in static memory.

Like the dynamically sized [mulle_pointerfifo](API_POINTERFIFO.md), it is a
bounded, non-blocking FIFO for exactly **one producer thread and one
consumer thread** (SPSC). `NULL` can not be stored, because `NULL` signals
"empty" on read.

All functions of the fixed FIFOs are underscore-prefixed: they do not check
their `fifo` argument for `NULL`. There are no NULL-tolerant wrapper
variants.


## Functions

### _mulle__pointerfifo32_init

```c
void   _mulle__pointerfifo32_init( struct mulle__pointerfifo32 *p);
```

Initializes the FIFO. Must complete before producer or consumer start.


### _mulle__pointerfifo32_done

```c
void   _mulle__pointerfifo32_done( struct mulle__pointerfifo32 *p);
```

Does nothing: the storage is part of the struct, so there is nothing to
free. Provided for symmetry with the dynamic FIFO.


### _mulle__pointerfifo32_write

```c
int   _mulle__pointerfifo32_write( struct mulle__pointerfifo32 *p,
                                   void                        *pointer);
```

Adds `pointer` to the rear of the FIFO. Returns `0` on success, `-1` if the
FIFO is full, and `-2` if `pointer` is `NULL`. Never blocks.

Only the producer thread may call this function.


### _mulle__pointerfifo32_read

```c
void   *_mulle__pointerfifo32_read( struct mulle__pointerfifo32 *p);
```

Removes and returns the oldest pointer in the FIFO, or `NULL` if the FIFO is
empty. Never blocks.

Only the consumer thread may call this function.


### _mulle__pointerfifo32_get_count

```c
unsigned int   _mulle__pointerfifo32_get_count( struct mulle__pointerfifo32 *p);
```

Returns the number of pointers currently stored. This is a single atomic
read of the shared counter: the value is exact at the moment it is read,
but may be stale by the time the caller acts on it. May be called from any
thread.


## Example

```c
#include <mulle-fifo/mulle-fifo.h>

#include <stdio.h>


int   main( void)
{
   struct mulle__pointerfifo32   fifo;
   void                          *pointer;
   int                           value;

   _mulle__pointerfifo32_init( &fifo);

   value = 42;
   if( _mulle__pointerfifo32_write( &fifo, &value) == 0)
      printf( "written\n");

   pointer = _mulle__pointerfifo32_read( &fifo);
   if( pointer)
      printf( "read: %d\n", *(int *) pointer);

   _mulle__pointerfifo32_done( &fifo);

   return( 0);
}
```
