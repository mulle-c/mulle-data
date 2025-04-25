# mulle-hash

**mulle-data** provides hash functions for arbitrary bytes and strings.
Currently it uses [xxHash](https://github.com/Cyan4973/xxHash) for byte
hashing and fnv1a for strings.

## Functions

- `mulle_hash_avalanche32(uint32_t h)`: This function takes a 32-bit unsigned integer `h` as input and returns a 32-bit hash value. It uses the avalanche effect to ensure that small changes in the input lead to significant changes in the output hash.

- `mulle_hash_avalanche64(uint64_t h)`: Similar to the previous function, this function takes a 64-bit unsigned integer `h` as input and returns a 64-bit hash value.

- `mulle_hash_avalanche(uintptr_t h)`: This function is a wrapper around the previous two functions. It takes an unsigned integer `h` of the size of a pointer and returns a hash value of the same size. Depending on the size of a pointer on the system, it calls either `mulle_hash_avalanche32()` or `mulle_hash_avalanche64()`.

- `mulle_integer_hash(uintptr_t p)`: This function takes an unsigned integer `p` and returns its hash value by calling `mulle_hash_avalanche()`.

- `mulle_pointer_hash(void *p)`: This function takes a pointer `p` and returns its hash value by calling `mulle_hash_avalanche()` with the pointer cast to an unsigned integer.

- `mulle_float_hash(float f)`: This function takes a float `f` and returns its hash value by calling `mulle_integer_hash()` with the float value cast to a 32-bit integer.

- `mulle_double_hash(double f)`: This function takes a double `f` and returns its hash value by calling `mulle_float_hash()` with the double value cast to a float.

- `mulle_long_double_hash(long double ld)`: This function takes a long double `ld` and returns its hash value by calling `mulle_double_hash()` with the long double value cast to a double.

- `mulle_long_long_hash(long long value)`: This function takes a long long `value` and returns its hash value by calling `mulle_hash_avalanche64()` with the long long value cast to a 64-bit integer.

- `mulle_hash_chained_32(void *bytes, size_t length, void **state_p)`: This function takes a pointer to a byte array, its length, and a pointer to a state pointer. It uses xxHash's streaming interface to calculate a 32-bit hash value. The state must be initialized to NULL for the first call. Call with length=0 to get the final hash value.

- `mulle_hash_chained_64(void *bytes, size_t length, void **state_p)`: Similar to the previous function, this function takes a pointer to a byte array, its length, and a pointer to a state pointer. It uses xxHash's streaming interface to calculate a 64-bit hash value. The state must be initialized to NULL for the first call. Call with length=0 to get the final hash value.

- `_mulle_hash_chained(void *bytes, size_t length, void **state_p)`: This function is a wrapper around the previous two functions. It takes a pointer to a byte array, its length, and a pointer to a state pointer. Depending on the size of a pointer on the system, it calls either `mulle_hash_chained_32()` or `mulle_hash_chained_64()`.

- `mulle_hash_chained(void *bytes, size_t length, void **state_p)`: This function takes a pointer to a byte array, its length, and a pointer to a state pointer. If the pointer is `NULL`, it returns `0`. Otherwise, it calls `_mulle_hash_chained()` with the provided input.

Example usage of chained hashing:
```c
void       *state = NULL;  // important!
uintptr_t  hash;

(void) mulle_hash_chained( "VfL", 3, &state);
(void) mulle_hash_chained( "Bochum", 6, &state);
hash = mulle_hash_chained( NULL, 0, &state);
```
