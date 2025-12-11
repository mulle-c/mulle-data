# mulle-data Library Documentation for AI

## 1. Introduction & Purpose

**mulle-data** provides foundational data structures and utilities for efficient data manipulation in the mulle-c ecosystem. It offers:

- **mulle_data**: A container struct that pairs a byte pointer with a length, simplifying the passing of raw memory blocks
- **Hash functions**: Multiple cryptographic and non-cryptographic hash algorithms (FNV-1a, MurmurHash3, FarmHash) for different use cases
- **mulle_range**: A struct representing ranges with location and length, enabling efficient range operations (intersection, union, subtraction)
- **Prime numbers**: Pre-computed primes for hashtable sizing
- **Sorting**: A cross-platform `mulle_qsort` implementation

This library is a foundational component of mulle-core and provides essential utilities for container libraries, hashtables, and other data structures that need consistent hashing and range handling.

## 2. Key Concepts & Design Philosophy

- **Simplicity**: Structures are minimal and rely on standard C types (void*, size_t, uintptr_t)
- **Platform consistency**: Hash functions and sorting provide identical behavior across platforms by avoiding platform-dependent implementations
- **Performance**: Inline functions are used extensively to avoid function call overhead; chained hashing allows progressive hashing of large data
- **Dual-width support**: Most functions support both 32-bit and 64-bit implementations, selecting at runtime based on `uintptr_t` size
- **Composite ranges**: Ranges can overlap, intersect, and be manipulated while maintaining validity; a range with zero length can be valid

## 3. Core API & Data Structures

### 3.1. `mulle-data.h`

#### `struct mulle_data`
- **Purpose**: Encapsulates a byte pointer and its length. Eliminates passing separate `bytes` and `length` parameters.
- **Key Fields**:
  - `void *bytes`: Pointer to the byte buffer
  - `size_t length`: Length of the buffer in bytes
- **Lifecycle**:
  - `mulle_data_make(bytes, length)`: Create a mulle_data struct from bytes and length
  - `mulle_data_make_empty()`: Create an empty mulle_data (bytes points to "", length = 0)
  - `mulle_data_make_invalid()`: Create an invalid mulle_data (bytes = NULL, length = 0)
- **Inspection**:
  - `mulle_data_is_empty(data)`: Check if length is 0
  - `mulle_data_is_invalid(data)`: Check if bytes is NULL
  - `mulle_data_assert(data)`: Assert that if length > 0, bytes is non-NULL
- **Operations**:
  - `mulle_data_hash(data)`: Compute hash of the data bytes using FarmHash
  - `mulle_data_hash_chained(data, state_p)`: Hash progressively (for streaming/large data)
  - `mulle_data_subdata(data, range)`: Extract a subrange as a new mulle_data
  - `mulle_data_search_data(haystack, needle)`: Find needle within haystack, return pointer or NULL

### 3.2. `mulle-hash.h`

Provides multiple hashing strategies with consistent API across 32-bit and 64-bit platforms.

#### Avalanche Functions
- **Purpose**: Improve distribution of hash values by "avalanching" bits
- `mulle_hash_avalanche32(h)`: 32-bit avalanche (MurmurHash3 algorithm)
- `mulle_hash_avalanche64(h)`: 64-bit avalanche
- `mulle_hash_avalanche(h)`: Platform-appropriate avalanche (dispatches based on `sizeof(uintptr_t)`)

#### Integer/Pointer/Float Hashing
- `mulle_integer_hash(p)`: Hash an integer using avalanche
- `mulle_pointer_hash(p)`: Hash a pointer using avalanche
- `mulle_float_hash(f)`: Hash a float by converting to uint32_t and avalanching
- `mulle_double_hash(f)`: Hash a double (converts to float then hashes)
- `mulle_long_double_hash(ld)`: Hash a long double
- `mulle_long_long_hash(value)`: Hash a 64-bit integer using 64-bit avalanche

#### Byte Array Hashing
- **Purpose**: Hash arbitrary byte sequences (FarmHash algorithm)
- `_mulle_hash_32(bytes, length)`: 32-bit hash of byte array
- `_mulle_hash_64(bytes, length)`: 64-bit hash of byte array
- `_mulle_hash(bytes, length)`: Platform-appropriate hash (NULL-safe version is `mulle_hash`)
- `mulle_hash(bytes, length)`: Public API (returns 0 if bytes is NULL)

#### Chained Hashing
- **Purpose**: Progressively hash data (useful for streaming or concatenating multiple buffers)
- `mulle_hash_chained_32(bytes, length, state_p)`: Add chunk to 32-bit hash state; pass NULL/0 to finalize
- `mulle_hash_chained_64(bytes, length, state_p)`: Add chunk to 64-bit hash state
- `mulle_hash_chained(bytes, length, state_p)`: Platform-appropriate chained hash
- **Pattern**: Initialize `state_p` to NULL, call multiple times with data chunks, finalize by calling with NULL/0 length

### 3.3. `mulle-fnv1a.h`

FNV-1a (Fowler–Noll–Vo) hash function, optimized for strings and small data.

#### Initialization
- `_mulle_fnv1a_init_32()`: Get 32-bit FNV-1a initial value (0x811c9dc5)
- `_mulle_fnv1a_init_64()`: Get 64-bit FNV-1a initial value (0xcbf29ce484222325ULL)
- `_mulle_fnv1a_init()`: Platform-appropriate init value

#### Single Step Hashing
- `_mulle_fnv1a_step_32(hash, byte)`: Update 32-bit hash with one byte
- `_mulle_fnv1a_step_64(hash, byte)`: Update 64-bit hash with one byte
- `_mulle_fnv1a_step(hash, byte)`: Platform-appropriate step

#### Buffer Hashing
- `_mulle_fnv1a_32(buf, len)`: Full 32-bit FNV-1a hash of buffer
- `_mulle_fnv1a_64(buf, len)`: Full 64-bit FNV-1a hash of buffer
- `_mulle_fnv1a(buf, len)`: Platform-appropriate hash
- `_mulle_fnv1a_32_inline(buf, len)`: Inline version (may be faster but larger code)
- `_mulle_fnv1a_64_inline(buf, len)`: Inline 64-bit version
- `_mulle_fnv1a_inline(buf, len)`: Platform-appropriate inline

#### Chained Hashing
- `_mulle_fnv1a_chained_32(buf, len, hash)`: Add buffer chunk to 32-bit FNV-1a hash
- `_mulle_fnv1a_chained_64(buf, len, hash)`: Add buffer chunk to 64-bit FNV-1a hash
- `_mulle_fnv1a_chained(buf, len, hash)`: Platform-appropriate chained
- Inline versions also available: `_mulle_fnv1a_chained_32_inline`, etc.

#### String Hashing
- `_mulle_string_hash(s)`: FNV-1a hash of null-terminated string
- `_mulle_string_hash_32(s)`: 32-bit version
- `_mulle_string_hash_64(s)`: 64-bit version
- `_mulle_string_hash_chained(s, hash)`: Chain string into existing hash
- `_mulle_string_hash_chained_32(s, hash)`: 32-bit chained
- `_mulle_string_hash_chained_64(s, hash)`: 64-bit chained

### 3.4. `mulle-range.h`

Comprehensive range representation and manipulation utilities.

#### `struct mulle_range`
- **Purpose**: Represent a contiguous range via location and length
- **Key Fields**:
  - `uintptr_t location`: Starting position
  - `uintptr_t length`: Size of range
- **Constants**:
  - `mulle_not_found_e`: INTPTR_MAX, represents "not found"
  - `mulle_range_location_min`: 0
  - `mulle_range_location_max`: INTPTR_MAX - 1
  - `mulle_range_zero`: { 0, 0 }

#### Construction
- `mulle_range_make(location, length)`: Create range from location and length
- `mulle_range_make_locations(loc1, loc2)`: Create range from two locations (handles ordering)
- `mulle_range_make_all()`: Create full range (location=0, length=-1, treated as max)
- `mulle_range_make_invalid()`: Create invalid range (location=INTPTR_MAX, length=0)

#### Validation & Inspection
- `mulle_range_is_valid(range)`: Check if range is valid (location <= max and no overflow)
- `mulle_range_equals(r1, r2)`: Check if two ranges are identical
- `mulle_range_get_min(range)`: Get minimum (start) location
- `mulle_range_get_max(range)`: Get maximum (one past end)
- `mulle_range_get_first_location(range)`: First location in range (or INTPTR_MAX if empty)
- `mulle_range_get_last_location(range)`: Last location in range (or INTPTR_MAX if empty)

#### Location Tests
- `mulle_range_contains_location(range, loc)`: Check if location is within range
- `mulle_range_contains(big, small)`: Check if big range contains small range
- `mulle_range_less_than_location(range, loc)`: Last location < loc?
- `mulle_range_less_than_or_equal_to_location(range, loc)`: Last location <= loc?
- `mulle_range_greater_than_location(range, loc)`: First location > loc?
- `mulle_range_greater_than_or_equal_to_location(range, loc)`: First location >= loc?
- `mulle_range_equal_to_location(range, loc)`: First location == loc?
- `mulle_range_distance_to_location(range, loc)`: Distance from range to location

#### Range Operations
- `mulle_range_validate_against_length(range, len)`: Clamp range to fit within a length (handles -1 as "full")
- `mulle_range_intersection(r1, r2)`: Compute overlap of two ranges (returns invalid if no overlap)
- `mulle_range_intersects(r1, r2)`: Check if ranges overlap
- `mulle_range_union(r1, r2)`: Compute union of two ranges
- `mulle_range_subtract(a, b, result[2])`: Remove b from a; fills result array with 1-2 ranges (returns void)
- `mulle_range_subtract_location(a, loc, result[2])`: Remove single location from a (returns void)
- `mulle_range_insert(a, b, result[2])`: Insert b into a; returns count of result ranges (unsigned int)

#### Binary Search
- `mulle_range_contains_bsearch(buf, n, search)`: Find range in sorted array that contains search range
- `mulle_range_intersects_bsearch(buf, n, search)`: Find range in sorted array that intersects search

#### Macros
- `mulle_range_for(range, name)`: For-loop macro over all locations in range

### 3.5. `mulle-prime.h`

Pre-computed prime numbers for hashtable sizing.

- `mulle_prime_for_depth(depth)`: Get prime for depth (-32 to 32). Used with hashtable depth management
- `mulle_prime_hash_for_depth(value, depth)`: Compute hash modulo prime at depth (uses switch for performance)

### 3.6. `mulle-qsort.h`

Cross-platform quicksort implementation ensuring consistent behavior.

#### Callback Types
- `mulle_qsort_cmp_t`: Simple comparator `int cmp(void *a, void *b)`
- `mulle_qsort_r_cmp_t`: Comparator with context `int cmp(void *a, void *b, void *thunk)`

#### Functions
- `mulle_qsort(array, count, element_size, cmp)`: Sort using simple comparator
- `mulle_qsort_r(array, count, element_size, cmp, thunk)`: Sort with context

## 4. Performance Characteristics

- **Hash functions**:
  - `mulle_hash_avalanche*`: O(1) per integer/pointer
  - `mulle_hash*`: O(n) for n bytes; FarmHash is designed for good distribution with minimal collisions
  - `_mulle_fnv1a*`: O(n) for n bytes; faster than FarmHash for small strings (like ObjC selectors)
  - Chained hashing: Allows progressive hashing with state preservation; useful for streaming

- **Range operations**:
  - Most operations: O(1)
  - Binary search: O(log n) on sorted range arrays
  - Subtract/Union: O(1) but may return up to 2 ranges

- **Sorting**:
  - `mulle_qsort`: O(n log n) average, O(n²) worst-case; uses Bentley & McIlroy "Engineering a Sort Function"
  - Inline variant available for small datasets

- **Thread-safety**: None of the functions are thread-safe; external locking required if shared across threads

## 5. AI Usage Recommendations & Patterns

### Best Practices

1. **Use mulle_data for passing bytes**: Instead of passing `(void *bytes, size_t length)` pairs, use `struct mulle_data` to keep them together and avoid mistakes.

2. **Choose the right hash function**:
   - For **strings and small data** (e.g., ObjC selectors): Use `_mulle_fnv1a_*` (faster, cache-friendly)
   - For **arbitrary/large data**: Use `mulle_hash_*` (FarmHash, better distribution)
   - For **integers and pointers**: Use `mulle_integer_hash` or `mulle_pointer_hash` (avalanche-based)

3. **Use chained hashing for large/streaming data**: Initialize state to NULL, call multiple times, finalize with NULL/0 length.

4. **Range operations are composable**: Call `mulle_range_validate_against_length` after reading user input to safely validate.

5. **Binary search on range arrays**: Ensure ranges are sorted by location; use `mulle_range_contains_bsearch` or `mulle_range_intersects_bsearch`.

### Common Pitfalls

1. **Invalid range fields**: Do not directly access `_mulle_range_*` functions (leading underscore indicates internal use).

2. **Overflow in range arithmetic**: Check validity with `mulle_range_is_valid` after creating ranges from untrusted input.

3. **mulle_range_make_all() special case**: A range with `length == -1` is treated as "full" during validation; don't rely on this for general ranges.

4. **Forgetting to reset chained hash state**: After calling chained hash functions with NULL/0 length to get the final hash, reset `state_p` to NULL before hashing a new chain.

5. **String vs. buffer hashing**: `_mulle_fnv1a_32(s, strlen(s))` on a string gives the same result as `_mulle_string_hash_32(s)`; use string functions only if you have a C string without length.

## 6. Integration Examples

### Example 1: Hash arbitrary byte data

```c
#include <mulle-data/mulle-data.h>
#include <stdio.h>

int main() {
    uint8_t data[] = {1, 2, 3, 4, 5};
    struct mulle_data d = mulle_data_make(data, 5);
    
    uintptr_t hash = mulle_data_hash(d);
    printf("Hash: %zu\n", hash);
    return 0;
}
```

### Example 2: Hash multiple buffers progressively

```c
#include <mulle-data/mulle-data.h>
#include <stdio.h>

int main() {
    void *state = NULL;
    
    // Hash first chunk
    mulle_hash_chained("part1", 5, &state);
    
    // Hash second chunk
    mulle_hash_chained("part2", 5, &state);
    
    // Finalize and get hash
    uintptr_t hash = mulle_hash_chained(NULL, 0, &state);
    
    printf("Combined hash: %zu\n", hash);
    return 0;
}
```

### Example 3: Range intersection

```c
#include <mulle-data/mulle-data.h>
#include <stdio.h>

int main() {
    struct mulle_range r1 = mulle_range_make(10, 20);  // 10-29
    struct mulle_range r2 = mulle_range_make(20, 30);  // 20-49
    
    struct mulle_range overlap = mulle_range_intersection(r1, r2);
    
    if (mulle_range_is_valid(overlap)) {
        printf("Overlap: %zu-%zu (length %zu)\n", 
               overlap.location, 
               mulle_range_get_max(overlap) - 1, 
               overlap.length);
    }
    return 0;
}
```

### Example 4: Extract subrange from data

```c
#include <mulle-data/mulle-data.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[] = "Hello, World!";
    struct mulle_data data = mulle_data_make(buffer, 13);
    
    // Extract "World" (positions 7-11)
    struct mulle_range range = mulle_range_make(7, 5);
    struct mulle_data sub = mulle_data_subdata(data, range);
    
    if (!mulle_data_is_invalid(sub)) {
        printf("%.*s\n", (int)sub.length, (char *)sub.bytes);  // prints "World"
    }
    return 0;
}
```

### Example 5: Sort integers using mulle_qsort

```c
#include <mulle-data/mulle-data.h>
#include <stdio.h>

static int compare_ints(void *a, void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return (x > y) - (x < y);
}

int main() {
    int array[] = {5, 2, 8, 1, 9};
    
    mulle_qsort(array, 5, sizeof(int), compare_ints);
    
    for (int i = 0; i < 5; i++)
        printf("%d ", array[i]);  // prints "1 2 5 8 9"
    printf("\n");
    return 0;
}
```

### Example 6: Use mulle_range_for macro

```c
#include <mulle-data/mulle-data.h>
#include <stdio.h>

int main() {
    struct mulle_range range = mulle_range_make(10, 5);  // 10-14
    
    mulle_range_for(range, i) {
        printf("%zu ", i);  // prints "10 11 12 13 14 "
    }
    printf("\n");
    return 0;
}
```

## 7. Dependencies

- `mulle-c11`: Cross-platform C compiler glue and C11 conveniences

