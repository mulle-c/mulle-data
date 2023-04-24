# mulle-hash

**mulle-data** provides a hash function for arbitrary bytes and a hash
functions for strings.
Currently it uses [farmhash](//github.com/google/farmhash) for the byte
hashing and fnv1a for strings. But this may change in the future.

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

- `_mulle_hash_chained_32(void *bytes, size_t length, uint32_t hash)`: This function takes a pointer to a byte array `bytes`, its length `length`, and a 32-bit hash value `hash` as input. It returns a new 32-bit hash value based on the input data and the provided hash value.

- `_mulle_hash_chained_64(void *bytes, size_t length, uint64_t hash)`: Similar to the previous function, this function takes a pointer to a byte array, its length, and a 64-bit hash value as input. It returns a new 64-bit hash value based on the input data and the provided hash value.

- `_mulle_hash_chained(void *bytes, size_t length, uintptr_t hash)`: This function is a wrapper around the previous two functions. It takes a pointer to a byte array, its length, and an unsigned integer of the size of a pointer as input. Depending on the size of a pointer on the system, it calls either `_mulle_hash_chained_32()` or `_mulle_hash_chained_64()`.

- `mulle_hash_chained(void *bytes, size_t length, uintptr_t hash)`: This function takes a pointer to a byte array, its length, and an unsigned integer of the size of a pointer as input. If the pointer is `NULL`, it returns `0`. Otherwise, it calls `_mulle_hash_chained()` with the provided input.

- `_mulle_hash_32(void *bytes, size_t length)`: This function takes a pointer to a byte array and its length as input. It returns a 32-bit hash value based on the input data.

- `_mulle_hash_64(void *bytes, size_t length)`: Similar to the previous function, this function takes a pointer to a byte array and its length as input. It returns a 64-bit hash value based on the input data.

- `_mulle_hash(void *bytes, size_t length)`: This function is a wrapper around the previous two functions. It takes a pointer to a byte array and its length as input. Depending on the size of a pointer on the system, it calls either `_mulle_hash_32()` or `_mulle_hash_64()`.

``` c
char data[] = "Hello, world!";
uintptr_t hash = mulle_hash(data, sizeof(data) - 1);
printf("Hash: %lu\n", hash);
```

> TODO: maybe rename `mulle_data_make_empty` to `mulle_data_zero`
> and `mulle_data_make_invalid` to `mulle_data_null` to be sameish with
> *mulle-geometry*

