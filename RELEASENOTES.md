## 0.5.0




feature: add cross-platform qsort and range utilities

* new `mulle_qsort_r()` function with BSD `qsort_r` implementation for API consistency across platforms
* `mulle_range_equals()` checks if two ranges are identical
* `mulle_range_intersects()` tests if two ranges overlap
* `mulle_range_equal_to_location()` checks if location matches range start
* `mulle_range_intersection()` replaces `mulle_range_intersect()` with better naming
