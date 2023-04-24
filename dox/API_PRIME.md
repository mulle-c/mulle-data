# mulle-prime

Functions dealing with prime numbers.


## Functions

### `mulle_prime_for_depth( int depth )`

This function returns a prime number based on the given depth value. The depth
value can range from -32 to 32, and the function uses an array of prime numbers
to return the prime number at the specified depth.

**Parameters:**
- `int depth`: The depth value for which the prime number is required. It
should be between -32 and 32.

**Returns:**
- `uintptr_t`: The prime number corresponding to the given depth.

**Example:**
```c
int depth = 5;
uintptr_t prime = mulle_prime_for_depth(depth);
printf("Prime number for depth %d is %lu\n", depth, prime);
```

### `mulle_prime_hash_for_depth( uintptr_t value, int depth )`

This function calculates the hash value for the given input value and depth
using modulo operation with prime numbers. It uses a switch-case statement to
compute the hash value for different depths.

**Parameters:**

- `uintptr_t value`: The input value for which the hash value is required.
- `int depth`: The depth value to be used for calculating the hash. It should be between -32 and 32.

**Returns:**

- `uintptr_t`: The hash value for the given input value and depth.

**Example:**

```c
uintptr_t input_value = 12345;
int depth = 5;
uintptr_t hash_value = mulle_prime_hash_for_depth(input_value, depth);
printf("Hash value for input %lu and depth %d is %lu\n", input_value, depth, hash_value);
```