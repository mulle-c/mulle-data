# mulle-hash

**mulle-data** provides hash functions for arbitrary bytes and strings.
Currently it uses [xxHash](https://github.com/Cyan4973/xxHash) for byte
hashing and fnv1a for strings.

## ⚠️ Portability Warning

`mulle_hash()`, `mulle_integer_hash()`, `mulle_pointer_hash()` and friends
return a **pointer-width dependent** hash. The same bytes produce different
values on 32-bit vs 64-bit platforms. These functions are designed for
**in-process hash tables only**.

**Do NOT** persist these values to disk, send them over a wire, or share them
between processes of different pointer widths (e.g. a 32-bit worker talking to
a 64-bit coordinator via shared memory or IPC).

For width-independent hashing use `mulle_hash_32()` or `mulle_hash_64()`.

## Width-independent functions

- `mulle_hash_32(void *bytes, size_t length)`: Computes a 32-bit xxHash (XXH32, seed 0). The result is identical on 32-bit and 64-bit platforms. NULL bytes are treated as `""`.

- `mulle_hash_64(void *bytes, size_t length)`: Computes a 64-bit xxHash (XXH64, seed 0). The result is identical on 32-bit and 64-bit platforms. NULL bytes are treated as `""`.

Use these when the hash must be stable across architectures, e.g. for
serialisation, protocol keys, or cross-process shared memory.

## Pointer-width functions

- `mulle_hash(void *bytes, size_t length)`: Pointer-width convenience wrapper. Calls `mulle_hash_32` on 32-bit and `mulle_hash_64` on 64-bit. NULL bytes are treated as `""` (hashes the empty string). **Process-local only.**

## Functions

- `mulle_hash_avalanche32(uint32_t h)`: This function takes a 32-bit unsigned integer `h` as input and returns a 32-bit hash value. It uses the avalanche effect to ensure that small changes in the input lead to significant changes in the output hash.

- `mulle_hash_avalanche64(uint64_t h)`: Similar to the previous function, this function takes a 64-bit unsigned integer `h` as input and returns a 64-bit hash value.

- `mulle_hash_avalanche(uintptr_t h)`: This function is a wrapper around the previous two functions. It takes an unsigned integer `h` of the size of a pointer and returns a hash value of the same size. Depending on the size of a pointer on the system, it calls either `mulle_hash_avalanche32()` or `mulle_hash_avalanche64()`.

- `mulle_integer_hash(uintptr_t p)`: This function takes an unsigned integer `p` and returns its hash value by calling `mulle_hash_avalanche()`.

- `mulle_pointer_hash(void *p)`: This function takes a pointer `p` and returns its hash value by calling `mulle_hash_avalanche()` with the pointer cast to an unsigned integer.

- `mulle_float_hash(float f)`: This function takes a float `f`, canonicalises negative zero to positive zero, and returns its hash value by calling `mulle_integer_hash()` with the float value reinterpreted as a 32-bit integer.

- `mulle_double_hash(double f)`: This function takes a double `f`, canonicalises negative zero to positive zero, and returns its hash value by hashing the full 64-bit representation. On 64-bit platforms it uses `mulle_hash_avalanche64()`; on 32-bit it folds the halves and uses `mulle_hash_avalanche32()`.

- `mulle_long_double_hash(long double ld)`: This function takes a long double `ld` and returns its hash value by calling `mulle_double_hash()` with the long double value cast to a double.

- `mulle_long_long_hash(long long value)`: This function takes a long long `value` and returns its hash value. On 64-bit platforms it uses `mulle_hash_avalanche64()`; on 32-bit it folds the two halves together and uses `mulle_hash_avalanche32()`. For values that fit in `uintptr_t`, the result is guaranteed to equal `mulle_integer_hash()` on all platforms.

- `mulle_hash_chained_32(void *bytes, size_t length, void **state_p)`: This function takes a pointer to a byte array, its length, and a pointer to a state pointer. It uses xxHash's streaming interface to calculate a 32-bit hash value. The state must be initialized to NULL for the first call. Pass bytes=NULL to finalise and retrieve the hash.

- `mulle_hash_chained_64(void *bytes, size_t length, void **state_p)`: Similar to the previous function, this function takes a pointer to a byte array, its length, and a pointer to a state pointer. It uses xxHash's streaming interface to calculate a 64-bit hash value. The state must be initialized to NULL for the first call. Pass bytes=NULL to finalise and retrieve the hash.

- `mulle_hash_chained(void *bytes, size_t length, void **state_p)`: This function is a pointer-width wrapper. Depending on the size of a pointer on the system, it calls either `mulle_hash_chained_32()` or `mulle_hash_chained_64()`.

- `mulle_hash_chained_done(void **state_p)`: Finalises and releases the chained hash state, discarding the hash result. Call this to abandon a chained hash computation whose result is no longer needed. After this call, `*state_p` is NULL. Also available as `mulle_hash_chained_32_done` and `mulle_hash_chained_64_done`.

- `mulle_hash_chained_add(void *bytes, size_t length, void **state_p)`: Type-safe wrapper that feeds bytes into an ongoing hash computation. Returns `void` — there is no in-band sentinel to misinterpret. Also available as `mulle_hash_chained_32_add` and `mulle_hash_chained_64_add`.

- `mulle_hash_chained_final(void **state_p)`: Finalises the chained hash and returns the hash value. After this call, `*state_p` is NULL. Also available as `mulle_hash_chained_32_final` and `mulle_hash_chained_64_final`.

Example usage of chained hashing (preferred style):
```c
void       *state = NULL;  // important!
uintptr_t  hash;

mulle_hash_chained_add( "VfL", 3, &state);
mulle_hash_chained_add( "Bochum", 6, &state);
hash = mulle_hash_chained_final( &state);
```

Legacy style (still works, but the mid-chain return value must be discarded):
```c
void       *state = NULL;
uintptr_t  hash;

(void) mulle_hash_chained( "VfL", 3, &state);
(void) mulle_hash_chained( "Bochum", 6, &state);
hash = mulle_hash_chained( NULL, 0, &state);
```
