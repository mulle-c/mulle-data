# mulle-fnv1a

The provided code implements the FNV-1a hash algorithm in C. The FNV-1a hash is a fast, non-cryptographic hash function that is useful for hash tables, checksums, and other data integrity applications. The implementation supports both 32-bit and 64-bit hash values. Here's a brief documentation for the main functions:

1. `_mulle_fnv1a_init_32(void)`: Initializes a 32-bit FNV-1a hash with the predefined constant `MULLE_FNV1A_32_INIT`.

   Example:
   ```c
   uint32_t hash = _mulle_fnv1a_init_32();
   ```

2. `_mulle_fnv1a_init_64(void)`: Initializes a 64-bit FNV-1a hash with the predefined constant `MULLE_FNV1A_64_INIT`.

   Example:
   ```c
   uint64_t hash = _mulle_fnv1a_init_64();
   ```

3. `_mulle_fnv1a_step_32(uint32_t hash, unsigned char value)`: Performs a single step of the 32-bit FNV-1a hash algorithm, updating the hash with the input `value`. Returns the updated hash.

   Example:
   ```c
   uint32_t updated_hash = _mulle_fnv1a_step_32(hash, value);
   ```

4. `_mulle_fnv1a_step_64(uint64_t hash, unsigned char value)`: Performs a single step of the 64-bit FNV-1a hash algorithm, updating the hash with the input `value`. Returns the updated hash.

   Example:
   ```c
   uint64_t updated_hash = _mulle_fnv1a_step_64(hash, value);
   ```

5. `_mulle_fnv1a_chained_32(void *buf, size_t len, uint32_t hash)`: Computes the 32-bit FNV-1a hash of the buffer `buf` with length `len`, using the input `hash` as the starting value. Returns the calculated hash.

   Example:
   ```c
   uint32_t final_hash = _mulle_fnv1a_chained_32(buffer, length, initial_hash);
   ```

6. `_mulle_fnv1a_chained_64(void *buf, size_t len, uint64_t hash)`: Computes the 64-bit FNV-1a hash of the buffer `buf` with length `len`, using the input `hash` as the starting value. Returns the calculated hash.

   Example:
   ```c
   uint64_t final_hash = _mulle_fnv1a_chained_64(buffer, length, initial_hash);
   ```

7. `_mulle_string_hash_32(char *s)`: Computes the 32-bit FNV-1a hash of the null-terminated string `s`.

   Example:
   ```c
   uint32_t string_hash = _mulle_string_hash_32("example");
   ```

8. `_mulle_string_hash_64(char *s)`: Computes the 64-bit FNV-1a hash of the null-terminated string `s`.

   Example:
   ```c
   uint64_t string_hash = _mulle_string_hash_64("example");
   ```

There are also several inline functions provided for convenience, such as `_mulle_fnv1a_init()`, `_mulle_fnv1a_step()`, `_mulle_fnv1a()`, `_mulle_fnv1a_chained()`, and `_mulle_string_hash()`, which automatically choose between 32-bit and 64-bit hashes based on the size of `uintptr_t`.

