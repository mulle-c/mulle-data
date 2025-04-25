# mulle-data

The library deals with the `mulle_data` structure, which contains a pointer to
raw bytes and the length of the data in bytes.

```c
struct mulle_data
{
   void     *bytes;
   size_t   length;
};
```

1. `mulle_data_make` creates a `mulle_data` structure with the given bytes and length.

```c
struct mulle_data   data = mulle_data_make_empty( "foo", 4);
```

2. `mulle_data_make_empty` creates an empty `mulle_data` structure, with a `NULL` bytes pointer and a length of 0.

```c
struct mulle_data   data = mulle_data_make_empty()
```

3. `mulle_data_make_invalid` creates an invalid `mulle_data` structure, with a `NULL` bytes pointer and a length of `(size_t) -1`.

```c
struct mulle_data   data = mulle_data_make_invalid()
```

4. `mulle_data_is_empty` checks if the given `mulle_data` structure is empty, i.e., if its length is 0.

```c
struct mulle_data  data = mulle_data_make_empty();
int is_empty = mulle_data_is_empty( data);
```

5. `mulle_data_is_invalid` checks if the given `mulle_data` structure is invalid, i.e., if its length is `(size_t) -1`.

```c
struct mulle_data  data = mulle_data_make_empty();
int is_valid = ! mulle_data_is_invalid( data)
```

6. `mulle_data_hash` computes a hash value for the given `mulle_data` structure using either a 32-bit or 64-bit hash function, depending on the size of `uintptr_t`.

```c
uintptr_t hash =  mulle_data_hash( data);
```

7. `mulle_data_hash_chained` computes a chained hash value for the given `mulle_data` structure using either a 32-bit or 64-bit hash function, depending on the size of `uintptr_t`. The `hash` parameter is used as a seed for the hash function.

```c
void        *state = NULL;
uintptr_t   hash;

mulle_data_hash_chained( data, &state);
mulle_data_hash_chained( other_data, &state);
hash = mulle_data_hash_chained( mulle_data_make_empty(), &state);
```