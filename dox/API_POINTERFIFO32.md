# mulle-pointerfifo32

This library provides a fixed-size, thread-safe FIFO queue for pointers in C.

## Functions

### `mulle_pointerfifo32_init`

```c
void mulle_pointerfifo32_init( struct mulle_pointerfifo32 *p_fifo);
```

Initializes a pointer FIFO with the specified capacity.

- `p_fifo`: pointer to the pointer FIFO to initialize

### `mulle_pointerfifo32_done`

```c
void mulle_pointerfifo32_done( struct mulle_pointerfifo32 *p_fifo);
```

Destroys a pointer FIFO.

- `p_fifo`: pointer to the pointer FIFO to destroy

### `mulle_pointerfifo32_push`

```c
void mulle_pointerfifo32_push( struct mulle_pointerfifo32 *p_fifo,
                               void                       *p_value);
```

Pushes a value onto the back of a pointer FIFO.

- `p_fifo`: pointer to the pointer FIFO to push onto
- `p_value`: pointer to the value to push onto the FIFO

### `mulle_pointerfifo32_pop`

```c
void *mulle_pointerfifo32_pop( struct mulle_pointerfifo32 *p_fifo);
```

Pops a value from the front of a pointer FIFO.

- `p_fifo`: pointer to the pointer FIFO to pop from

Returns a pointer to the value popped from the FIFO, or `NULL` if the FIFO is empty.

### `mulle_pointerfifo32_count`

```c
size_t mulle_pointerfifo32_count( struct mulle_pointerfifo32 *p_fifo);
```

Returns the number of elements in a pointer FIFO.

- `p_fifo`: pointer to the pointer FIFO to count the elements of

Returns the number of elements in the FIFO.

### `mulle_pointerfifo32_is_full`

```c
int mulle_pointerfifo32_is_full( struct mulle_pointerfifo32 *p_fifo);
```

Checks if a pointer FIFO is full.

- `p_fifo`: pointer to the pointer FIFO to check if full

Returns `1` if the FIFO is full, `0` otherwise.

### `mulle_pointerfifo32_is_empty`

```c
int mulle_pointerfifo32_is_empty( struct mulle_pointerfifo32 *p_fifo);
```

Checks if a pointer FIFO is empty.

- `p_fifo`: pointer to the pointer FIFO to check if empty

Returns `1` if the FIFO is empty, `0` otherwise.

## Example Usage

```c
#include <stdio.h>
#include <stdlib.h>
#include "mulle-pointerfifo32.h"

int main() {
  struct mulle_pointerfifo32 fifo;
  mulle_pointerfifo32_init( &fifo);
  int value = 42;
  mulle_pointerfifo32_push( &fifo, &value);
  void *popped_value = mulle_pointerfifo32_pop( &fifo);
  printf("Popped value: %d\n", *(int*) popped_value);
  mulle_pointerfifo32_done( &fifo);
  return 0;
}
```
