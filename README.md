# mulle-data

#### #️⃣ A collection of hash functions

* bit avalance for integers and pointers
* FNV1A for hashing strings for hashtables
* farmhash for (large) data

It contains the convenient `struct mulle_data` to keep `bytes` and
`length` together and to pass it around.

And it contains `struct mulle_range`, which represents ranges of data with
a location (offset) and a length.


| Release Version
|-----------------------------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-data.svg?branch=release) [![Build Status](https://github.com/mulle-c/mulle-data/workflows/CI/badge.svg?branch=release)](https://github.com/mulle-c/mulle-data/actions)



### You are here

![Overview](overview.dot.svg)


## Add

### Either: link library

Use [mulle-sde](//github.com/mulle-sde) to add mulle-buffer to your project:

```
mulle-sde dependency add --c --marks no-cmake-inherit --github mulle-c mulle-buffer
```

### Or: add Sources

Alternatively you can read [STEAL.md](//github.com/mulle-c11/dox/STEAL.md) on
how to add mulle-c source code into your own projects.


## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-data
and all its dependencies:

```
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-c/mulle-data/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                | Description
--------------------------------------------|-----------------------
[mulle-c11](//github.com/mulle-c/mulle-c11) | C compiler glue
[farmhash](//github.com/mulle-c/farmhash)   | Data hash function

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
