# mulle-range

This C code provides a set of functions to perform operations on `mulle_range` structures. The `mulle_range` structure represents a range with a starting
location and a length. The functions provided include:


## On `mulle_not_found_e` (read before filing a bug about it)

Locations are limited to `mulle_range_location_max`, which is
`mulle_not_found_e - 1`. This ceiling is deliberate and load bearing: it makes
`mulle_not_found_e` an **out-of-band** sentinel rather than an in-band one.
Because `mulle_range_is_valid` enforces the ceiling, no valid *non-empty* range
can have `get_first_location` or `get_last_location` return
`mulle_not_found_e` — that answer only ever means "empty range".

The practical cost is that byte ranges cap at `INTPTR_MAX`. On 64-bit that is
9.2 exabytes and unreachable. On 32-bit it is 2 GB, which a large mapping could
in principle exceed. Widening the type to the full `uintptr_t` span would
reclaim that upper half but would *create* a sentinel collision where none
exists today, so it is not a trade worth making. `NSRange`/`NSNotFound` in
Foundation carry the identical limitation.

`test/60-misc/range-sentinel.c` pins these invariants.


1. `mulle_range_make`: Creates a new range with the specified location and length.

```c
struct mulle_range range = mulle_range_make(location, length);
```

2. `mulle_range_make_all`: Creates a range that covers everything from location 0 to the maximum possible range.

```c
struct mulle_range all_range = mulle_range_make_all();
```

3. `mulle_range_make_invalid`: Creates an invalid range with a location set to `mulle_not_found_e`.

```c
struct mulle_range invalid_range = mulle_range_make_invalid();
```

4. `mulle_range_is_valid`: Checks if the given range is valid.

```c
int is_valid = mulle_range_is_valid(range);
```

5. `mulle_range_get_max`: Calculates the end location of the given range.

```c
uintptr_t end = mulle_range_get_max(range);
```

6. `mulle_range_get_last_location`: Returns the last (maximum) location contained in the given range, i.e. `location + length - 1`. Returns `mulle_not_found_e` for empty ranges.

```c
uintptr_t last = mulle_range_get_last_location(range);
```

7. `mulle_range_contains_location`: Checks if the given range contains a specified location.

```c
int contains = mulle_range_contains_location(range, location);
```

8. `mulle_range_less_than_or_equal_to_location`: Checks if the given range is less than or equal to the specified location.

```c
int less_than_or_equal = mulle_range_less_than_or_equal_to_location(range, location);
```

9. `mulle_range_less_than_location`: Checks if the given range is less than the specified location.

```c
int less_than = mulle_range_less_than_location(range, location);
```

10. `mulle_range_greater_than_or_equal_to_location`: Checks if the given range is greater than or equal to the specified location.

```c
int greater_than_or_equal = mulle_range_greater_than_or_equal_to_location(range, location);
```

11. `mulle_range_greater_than_location`: Checks if the given range is greater than the specified location.

```c
int greater_than = mulle_range_greater_than_location(range, location);
```

12. `mulle_range_distance_to_location`: Calculates the distance between the given range and a specified location.

```c
uintptr_t distance = mulle_range_distance_to_location(range, location);
```

13. `mulle_range_validate_against_length`: Validates the given range against a specified length and returns a new range that fits within the specified length.

```c
struct mulle_range valid_range = mulle_range_validate_against_length(range, length);
```

14. `mulle_range_contains`: Checks if a given range (big) contains another range (small).

```c
int contains_range = mulle_range_contains(big_range, small_range);
```

15. `mulle_range_subtract_location`: Subtracts a single location from the given range and stores the resulting ranges (up to 2) in the `result` array.

```c
struct mulle_range result[2];
mulle_range_subtract_location(range, location, result);
```

16. `mulle_range_intersect`: This function takes two `mulle_range` structures as input and returns the intersection between them. If there is no intersection, it returns a range with zero length.

```c
struct mulle_range   mulle_range_intersect( struct mulle_range range,
                                            struct mulle_range other);
```

17. `mulle_range_union`: This function takes two `mulle_range` structures as input and returns their union. If one of the ranges is empty, it returns the other range.

```c
struct mulle_range   mulle_range_union( struct mulle_range range,
                                        struct mulle_range other);
```

18. `_mulle_range_hole_bsearch`: This function performs a binary search on an array of `mulle_range` structures, looking for a hole (a gap between ranges) that the given search location can fit in.

```c
unsigned int   _mulle_range_hole_bsearch( struct mulle_range *buf,
                                          unsigned int n,
                                          uintptr_t search_location);
```

19. `mulle_range_contains_bsearch`: This function performs a binary search on an array of `mulle_range` structures, looking for a range that contains the given search range.

```c
struct mulle_range   *mulle_range_contains_bsearch( struct mulle_range *buf,
                                                    unsigned int n,
                                                    struct mulle_range search);
```

20. `mulle_range_intersects_bsearch`: This function performs a binary search on an array of `mulle_range` structures, looking for a range that intersects the given search range.

```c
struct mulle_range   *mulle_range_intersects_bsearch( struct mulle_range *buf,
                                                      unsigned int n,
                                                      struct mulle_range search);
```

21. `mulle_range_subtract`: This function takes two `mulle_range` structures (a and b) and subtracts the second range (b) from the first range (a). The result (up to 2 ranges) is stored in the `result` array. Unused entries are set to zero-length.

```c
struct mulle_range result[ 2];
mulle_range_subtract( a, b, result);
```


These functions can be used to manipulate and work with ranges in your C code.