# mulle-fifo

#### 🐍 mulle-fifo small fixed sized producer/consumer FIFOs

Written for dual-thread configurations. There is a hardcoded 64 pointer sized
mulle--pointerfifo64 FIFO and there is a variable sized mulle--pointerfifo.
The size of the FIFOs can not be changed after init.


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
