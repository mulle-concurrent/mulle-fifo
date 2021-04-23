# mulle-fifo

#### 🐍 mulle-fifo fixed sized producer/consumer FIFOs holding `void *`

Written for dual-thread configurations. There is a collection of hardcoded size
FIFOs and there is a dynamic allocated FIFO.
The size of the dynamic allocated FIFOs can not be changed after init.

You can not store NULL pointers into the FIFO.

There are FIFOs of sizes 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192.
You can easily create your own custom size.


## Usage

### Fixed

`mulle__pointerfifo64` is  a fixed size 64 pointer FIFO.
Use `_mulle__pointerfifo128` for a 128 pointer FIFO etc.

```
void   _mulle__pointerfifo64_init( struct mulle__pointerfifo64 *p)
```

Call this to initalize the FIFO for use.


```
void   _mulle__pointerfifo64_done( struct mulle__pointerfifo64 *p)
```

You can call this when no other thread needs the FIFO anymore.


```
unsigned int   _mulle__pointerfifo64_get_count( struct mulle__pointerfifo64 *p)
```

Get the number of pointers stored. Thread safe even for multiple threads.


```
void   *_mulle__pointerfifo64_read( struct mulle__pointerfifo64 *p)
```

Read from the FIFO. Will return NULL if empty. Will not block.
Only one thread may access the read side.

```
int   _mulle__pointerfifo64_write( struct mulle__pointerfifo64 *p,
                                   void *pointer)
```

Write to the FIFO. Will return -1 if full, 0 on success. Will not block.
Only one thread may access the write side.


### Dynamic

The dynamic FIFO is like the static FIFO, except for the `init` and
`done` functions:

```
void   _mulle__pointerfifo_init( struct mulle__pointerfifo64 *p,
                                 unsigned int size,
                                 struct mulle_allocator *allocator)
```

Call this to initalize the FIFO for use. The size is set at runtime.


```
void   _mulle__pointerfifo_done( struct mulle__pointerfifo64 *p)
```

Call this to free the FIFO when no other thread needs it. This is necessary
to avoid leaks.



## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-fifo to your project:

``` console
mulle-sde dependency add --c --github mulle-concurrent mulle-fifo
```

## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-fifo
and all its dependencies:

```
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-concurrent/mulle-fifo/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                               | Description
-----------------------------------------------------------|-----------------------
[mulle-allocator](//github.com/mulle-c/mulle-allocator)    | Memory allocation wrapper
[mulle-thread](//github.com/mulle-concurrent/mulle-thread) | Thread wrapper

Install into `/usr/local`:

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
         -DCMAKE_PREFIX_PATH=/usr/local \
         -DCMAKE_BUILD_TYPE=Release .. ;
   make install
)
```

### Steal

Read [STEAL.md](//github.com/mulle-c11/dox/STEAL.md) on how to steal the
source code and incorporate it in your own projects.
