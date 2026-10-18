# mulle-data

#### #️⃣  A collection of hash functions

* bit avalance for integers and pointers
* FNV1A for hashing strings for hashtables
* farmhash for (large) data

It contains the convenient `struct mulle_data` to keep `bytes` and
`length` together and to pass it around.

And it contains `struct mulle_range`, which represents ranges of data with
a location (offset) and a length.




| Release Version                                       | Release Notes  | AI Documentation
|-------------------------------------------------------|----------------|---------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-data.svg) ![standard: C11](pix/c11.svg) ![apis: ansi](pix/apis-ansi.svg) ![memory: allocator](pix/memory-allocator.svg) ![threads: threadsafe](pix/thread-threadsafe.svg) [![Build Status](https://github.com/mulle-c/mulle-data/workflows/CI/badge.svg)](//github.com/mulle-c/mulle-data/actions) ![Coverage](https://img.shields.io/badge/coverage-97%25%C2%A0-2acf49) | [RELEASENOTES](RELEASENOTES.md) | [DeepWiki for mulle-data](https://deepwiki.com/mulle-c/mulle-data)


## API

| Documentation                     | Description
|-----------------------------------|-------------------
| [mulle-data](dox/API_DATA.md)     | `struct mulle_data` holds a pointer to a block of memory (`void *bytes`) and its length in bytes (`size_t length`).
| [mulle-fnv1a](dox/API_FNV1A.md)   | FNV-1a  is a fast, non-cryptographic hash that provides good distribution and low collisions for strings
| [mulle-hash](dox/API_HASH.md)     | MurmurHash3 and FarmHash for fast, efficient, and high-quality hashes of arbitraty data
| [mulle-prime](dox/API_PRIME.md)   | Prime number support for hashtables
| [mulle-range](dox/API_RANGE.md)   | `struct mulle_range` defines a range with a location and length


## Documentation & Guides

* [API Summary](asset/dox/api/toc)




### You are here

![Overview](overview.dot.svg)





## Add

### Add mulle-data via mulle-core

mulle-data is a component of the
[mulle-core](//github.com/mulle-core/mulle-core) library.
In your code include its umbrella header:

``` c
#include <mulle-core/mulle-core.h>
```

Add mulle-core to your `CMakeLists.txt` with
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

``` cmake
include( FetchContent)

set( MULLE__CORE_TAG "master" CACHE STRING "branch or tag to fetch mulle-core from")

FetchContent_Declare( MULLE__CORE
   GIT_REPOSITORY https://github.com/mulle-core/mulle-core.git
   GIT_TAG        "${MULLE__CORE_TAG}")
FetchContent_MakeAvailable( MULLE__CORE)

target_link_libraries( ${PROJECT_NAME} PUBLIC mulle-core)
```

Or add to your mulle-sde project with:

``` sh
mulle-sde add mulle-core/mulle-core
```




### Add mulle-data as a cmake subproject

In your code include its header:

``` c
#include <mulle-data/mulle-data.h>
```

Add mulle-data and its dependencies to your `CMakeLists.txt` with
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

``` cmake
include( FetchContent)

include_directories( SYSTEM "${CMAKE_BINARY_DIR}/include")

set( MULLE__C11_TAG "master" CACHE STRING "branch or tag to fetch mulle-c11 from")

FetchContent_Declare( MULLE__C11
   GIT_REPOSITORY https://github.com/mulle-c/mulle-c11.git
   GIT_TAG        "${MULLE__C11_TAG}")
FetchContent_MakeAvailable( MULLE__C11)

set( MULLE__DATA_TAG "master" CACHE STRING "branch or tag to fetch mulle-data from")

FetchContent_Declare( MULLE__DATA
   GIT_REPOSITORY https://github.com/mulle-c/mulle-data.git
   GIT_TAG        "${MULLE__DATA_TAG}")
FetchContent_MakeAvailable( MULLE__DATA)

target_link_libraries( ${PROJECT_NAME} PUBLIC mulle-data)
```

Or add to your mulle-sde project with:

``` sh
mulle-sde add github:mulle-c/mulle-data
```

## Individual Install

Install all the prerequisites.

``` bash
PREFIX=/tmp/usr/local
BUILD_DIR="mulle-data/build"

cmake -S "mulle-data" -B "${BUILD_DIR}"    \
  -DCMAKE_BUILD_TYPE="Release"                  \
  -DCMAKE_INSTALL_PREFIX="${PREFIX}"            \
  -DCMAKE_PREFIX_PATH="${PREFIX}"               \
  -DCMAKE_C_FLAGS="-I"${PREFIX}"/include"       \
&& cmake --build "${BUILD_DIR}"  --parallel     \
&& cmake --install "${BUILD_DIR}"
```


## Author

[Nat!](https://mulle-kybernetik.com/weblog) for Mulle kybernetiK  



