#  mulle_pointerfifo

A `mulle_pointerfifo` is a bounded, non-blocking FIFO queue for `void *`
pointers, with its capacity chosen at runtime. It is designed for exactly
**one producer thread and one consumer thread** (SPSC). It never grows,
never blocks, and never allocates during read or write.

The fixed-size variant is documented in [API_POINTERFIFO32](API_POINTERFIFO32.md).

The functions prefixed with an underscore do not check their `fifo` argument
for `NULL`. The same-named functions without the underscore are NULL-tolerant
wrappers.


## Contract

- Exactly one thread may call the write functions, exactly one thread may
  call the read functions. Calls from additional threads are forbidden.
- `init` must complete before producer or consumer start. `done` must only
  be called after both have stopped.
- The FIFO does not take ownership of the pointers stored in it. It never
  frees or otherwise touches the pointed-to objects.
- `NULL` can not be stored, because `NULL` signals "empty" on read.
- All internal synchronization uses sequentially consistent atomic operations
  (see `mulle-thread`). A successful `write` publishes both the pointer value
  and the contents of the pointed-to object; a subsequent `read` that observes
  the pointer may safely dereference it. No additional barriers are required.


## Functions

### mulle_pointerfifo_init

```c
void   mulle_pointerfifo_init( struct mulle_pointerfifo  *p,
                               unsigned int              size,
                               struct mulle_allocator    *allocator);
```

Initializes the FIFO with room for `size` pointers. `size` must be at
least 2 (checked with `assert`). Storage is allocated with `allocator`;
if `allocator` is `NULL`, the default allocator is used. Allocation failure
follows the `mulle_allocator` contract: the allocator's `fail` function is
called, which by default aborts the program.

`_mulle_pointerfifo_init` is the variant without the `NULL` check on `p`.


### mulle_pointerfifo_done

```c
void   mulle_pointerfifo_done( struct mulle_pointerfifo *p);
```

Frees the storage. Does not free or otherwise touch any pointers still in
the FIFO; drain it first if that matters to you. It is safe to call `done`
more than once. The FIFO must be re-initialized with `init` before reuse.

`_mulle_pointerfifo_done` is the variant without the `NULL` check on `p`.


### mulle_pointerfifo_write

```c
int   mulle_pointerfifo_write( struct mulle_pointerfifo *p,
                               void                     *pointer);
```

Adds `pointer` to the rear of the FIFO. Returns `0` on success, `-1` if the
FIFO is full, and `-2` if `pointer` is `NULL`. Never blocks. The safe
wrapper returns `-1` if `p` is `NULL`.

Only the producer thread may call this function.


### mulle_pointerfifo_read

```c
void   *mulle_pointerfifo_read( struct mulle_pointerfifo *p);
```

Removes and returns the oldest pointer in the FIFO, or `NULL` if the FIFO is
empty. Never blocks. The safe wrapper returns `NULL` if `p` is `NULL`.

Only the consumer thread may call this function.


### mulle_pointerfifo_get_count

```c
unsigned int   mulle_pointerfifo_get_count( struct mulle_pointerfifo *p);
```

Returns the number of pointers currently stored. This is a single atomic
read of the shared counter: the value is exact at the moment it is read,
but may be stale by the time the caller acts on it. May be called from any
thread. The safe wrapper returns `0` if `p` is `NULL`.


## Example

```c
#include <mulle-fifo/mulle-fifo.h>

#include <stdio.h>


int   main( void)
{
   struct mulle_pointerfifo   fifo;
   void                       *pointer;
   int                        value;

   mulle_pointerfifo_init( &fifo, 16, NULL);

   value = 42;
   if( mulle_pointerfifo_write( &fifo, &value) == 0)
      printf( "written\n");

   pointer = mulle_pointerfifo_read( &fifo);
   if( pointer)
      printf( "read: %d\n", *(int *) pointer);

   mulle_pointerfifo_done( &fifo);

   return( 0);
}
```
