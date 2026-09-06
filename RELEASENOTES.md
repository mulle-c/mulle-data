## 0.6.0







feature: add width-independent hashing and type-safe chained hash API

* new `mulle_hash_32()/mulle_hash_64()` give stable fixed-width hashes that agree across 32- and 64-bit processes
* new `mulle_hash_chained_add()/final()/done()` wrappers eliminate the NULL in-band sentinel for chained hashing
* new `mulle_data_equals()` and `mulle_data_compare()` for struct `mulle_data`
* `mulle_double_hash()` now hashes the full 64-bit representation instead of truncating through float
* float/double hashing canonicalises -0.0 to +0.0 so equal values hash identically
* `mulle_hash(NULL,` 0) now hashes the empty string instead of returning 0
* **BREAKING**: range binary search functions now take `uintptr_t` counts and `_mulle_range_hole_bsearch` returns `uintptr_t`
* `mulle_range_intersects()` no longer treats merely adjacent ranges as intersecting
* faster `mulle_data_search_data()` via memchr/memcmp; qsort and swap now guard against zero element size



* API documentation TOC restructured to asset/dox/api/toc/


### 0.5.2

Various small improvements
