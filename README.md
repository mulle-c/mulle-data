# mulle-data

#### #️⃣ A collection of hash functions

* bit avalance for integers and pointers
* FNV1A for hashing strings for hashtables
* farmhash for (large) data

It contains the convenient `struct mulle_data` to keep `bytes` and
`length` together and to pass it around.

And it contains `struct mulle_range`, which represents ranges of data with
a location (offset) and a length.


| Release Version                                       | Release Notes
|-------------------------------------------------------|--------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-data.svg?branch=release) [![Build Status](https://github.com/mulle-c/mulle-data/workflows/CI/badge.svg?branch=release)](//github.com/mulle-c/mulle-data/actions)| [RELEASENOTES](RELEASENOTES.md) |





## Hash functions

*mulle-data* uses various hash algorithms, which are not compatible with
each other. You can compare the hashes of two strings, but you can not compare
the returned hash by `_mulle_hash_string` for `"foo"` and the hash of
`mulle_data_hash( mulle_data_make( "foo", 4))` as one is using FNV1A and the
other is Farmhash (at time of writing).

The returned hash is of `uintptr_t` size, which should be a convenient size
for hash tables.


| Function               | Description
|------------------------|------------------------------
| `mulle_hash`           | hash a memory block
| `mulle_integer_hash`   | hash an integer value
| `mulle_pointer_hash`   | hash an pointer
| `mulle_float_hash`     | hash a `float`  floating point value
| `mulle_double_hash`    | hash a `double` floating point value
| `mulle_long_long_hash` | hash a `long long` integer value
| `mulle_hash_pointer`   | hash a pointer.
| `mulle_hash_string`    | hash a C string
| `mulle_data_hash`      | hash a mulle_data memory block



> TODO: rename mulle_data_make_empty to mulle_data_zero
> and mulle_data_make_invalid to mulle_data_null to be sameish with
> mulle-geometry


### You are here

![Overview](overview.dot.svg)





## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-data to your project:

``` sh
mulle-sde add github:mulle-c/mulle-data
```

To only add the sources of mulle-data with dependency
sources use [clib](https://github.com/clibs/clib):


``` sh
clib install --out src/mulle-c mulle-c/mulle-data
```

Add `-isystem src/mulle-c` to your `CFLAGS` and compile all the sources that were downloaded with your project.


## Install

### Install with mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-data and all dependencies:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-c/mulle-data/archive/latest.tar.gz
```

### Manual Installation

Install the requirements:

| Requirements                                 | Description
|----------------------------------------------|-----------------------
| [mulle-c11](https://github.com/mulle-c/mulle-c11)             | 🔀 Cross-platform C compiler glue (and some cpp conveniences)

Install **mulle-data** into `/usr/local` with [cmake](https://cmake.org):

``` sh
cmake -B build \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_PREFIX_PATH=/usr/local \
      -DCMAKE_BUILD_TYPE=Release &&
cmake --build build --config Release &&
cmake --install build --config Release
```


## Author

[Nat!](https://mulle-kybernetik.com/weblog) for Mulle kybernetiK



