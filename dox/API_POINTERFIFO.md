#  FIFO

A FIFO (First-In-First-Out) is a data structure that follows the principle that the first element added to the container will be processed first. It is essentially a queue, where elements are inserted at the rear end and removed from the front end. FIFOs are used in various computer applications and have significant importance in scheduling algorithms and network communication. They provide a fair processing order, ensuring that the element that has entered first will get the opportunity to leave first. For more information, you can refer to the [Wikipedia page on Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)).


### mulle__pointerfifo_init

```c
void   mulle__pointerfifo_init(struct mulle__pointerfifo *p, void *buf, size_t size, struct mulle_allocator *allocator);
```

- **Function Signature**: `mulle__pointerfifo_init`
- **Parameters**:
  - `p`: A pointer to the `mulle__pointerfifo` structure.
  - `buf`: A pointer to the memory buffer that will be used as the storage for the FIFO.
  - `size`: The size (in number of elements) of the `buf` array.
  - `allocator`: A pointer to the `mulle_allocator` structure that defines the memory allocation strategy to be used.

This function initializes a `mulle__pointerfifo` structure with the provided parameters. It sets up the internal state of the FIFO, including the buffer, its size, and the allocator.

### mulle__pointerfifo_done

```c
void   mulle__pointerfifo_done(struct mulle__pointerfifo *p);
```

- **Function Signature**: `mulle__pointerfifo_done`
- **Parameters**:
  - `p`: A pointer to the `mulle__pointerfifo` structure.

This function cleans up the internal state of the `mulle__pointerfifo` structure and releases any resources held by it.

### mulle__pointerfifo_write

```c
int   mulle__pointerfifo_write(struct mulle__pointerfifo *p, void *item);
```

- **Function Signature**: `mulle__pointerfifo_write`
- **Parameters**:
  - `p`: A pointer to the `mulle__pointerfifo` structure.
  - `item`: A pointer to the data item to be added to the FIFO.

This function writes an item to the `mulle__pointerfifo`. If the FIFO is full, it returns a non-zero value, otherwise, it returns zero.

### mulle__pointerfifo_read

```c
void  *mulle__pointerfifo_read(struct mulle__pointerfifo *p);
```

- **Function Signature**: `mulle__pointerfifo_read`
- **Parameters**:
  - `p`: A pointer to the `mulle__pointerfifo` structure.

This function reads an item from the `mulle__pointerfifo`. If the FIFO is empty, it returns `NULL`, otherwise, it returns a pointer to the read item.

### Example

Here is an example of how to use these functions:

```c
#include "mulle--pointerfifo.h"
#include "mulle-allocator.h"

int main() {
    struct mulle__pointerfifo fifo;
    struct mulle_allocator *allocator = &mulle_default_allocator;
    void *buffer[10];

    mulle__pointerfifo_init(&fifo, buffer, 10, allocator);

    int value = 42;
    if (mulle__pointerfifo_write(&fifo, &value) == 0) {
        printf("Value written to the FIFO.\n");
    }

    int *read_value = mulle__pointerfifo_read(&fifo);
    if (read_value != NULL) {
        printf("Value read from the FIFO: %d\n", *read_value);
    }

    mulle__pointerfifo_done(&fifo);
    return 0;
}
```

This example initializes a `mulle__pointerfifo` with a buffer of size 10, writes an integer value to the FIFO, reads the value back, and then cleans up the FIFO.