### 0.5.1








* chained hash functions `(mulle_hash_chained_32/64)` now treat zero-length chunks as updates and only finalize when bytes == NULL, preventing premature finalization and supporting empty-chunk sequences
* make range helpers (e.g. `mulle_range_intersects,` `_mulle_range_hole_bsearch)` public so callers can link against them
* add tests exercising chained-hash edge cases (zero-length, multi-chunk sequences)
