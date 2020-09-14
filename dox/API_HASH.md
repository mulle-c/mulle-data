# Hash

**mulle-container** provides a hash function for arbitrary bytes.
Currently it uses [farmhash](//github.com/google/farmhash) for the actual
hashing. But this may change in the future.

## Functions

### `mulle_hash_avalanche`

```
uintptr_t   mulle_hash_avalanche( uintptr_t h)
```

An `uintptr_t` sized avalance. Returns an avalance on `h`. This is useful to
make constants work better in hashtables, that don't use primes. Taken from
[MurmurHash3](//code.google.com/p/smhasher/wiki/MurmurHash3)


### `mulle_hash_integer`

```
uintptr_t   mulle_hash_integer( uintptr_t p)
```

Convenience synonym for `mulle_hash_avalanche`.


### `mulle_pointer_hash`

```
uintptr_t   mulle_pointer_hash( void *p)
```

Type convenience for `mulle_hash_avalanche`.


### `mulle_hash`

```
uintptr_t   mulle_hash( void *buf, size_t len)
```

Create a hash value from `len` bytes in `buf`.


### `mulle_hash_chained`

```
uintptr_t   mulle_hash_chained( void *buf, size_t len, uintptr_t hash)
```

Use `mulle_hash_chained` to incrementally calculate a hash. The initital `hash`
value is called the seed. To the knowledge of the author, this can be
initialized with 0 without problems.

Example:

```
   hash = 0;
   hash = mulle_hash_chained( header, 32, hash);
   hash = mulle_hash_chained( buf, length, hash);
   return( hash);
```






