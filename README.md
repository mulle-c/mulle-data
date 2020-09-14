# mulle-data

#### #️⃣ A collection of hash functions

* bit avalance for integers and pointers
* FNV1A for hashing strings for hashtables
* farmhash for (large) data

It also contains the convenient `struct mulle_data` to keep `bytes` and
`length` together and to pass it around.


## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-data to your project:

``` console
mulle-sde dependency add --c --github <|GITHUB_USER|> mulle-data
```

## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-data
and all its dependencies:

```
mulle-sde install --prefix /usr/local \
   https://github.com/<|GITHUB_USER|>/mulle-data/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                      | Description
--------------------------------------------------|-----------------------
[mulle-c11](//github.com/mulle-c/mulle-c11)       | C compile glue
[farmhash](//github.com/mulle-c/farmhash)         | Data hash function

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
