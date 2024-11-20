### 0.3.1




* improved a test

## 0.3.0

* changed farmhash to be stable with NDEBUG or not NDEBUG
* **BREAKING** `mulle_range_subtract` now always returns two ranges and the first one can be NULL, this is actually more practical
* this also affects `mulle_range_subtract_location`
* added `mulle_data_search_data` and `mulle_data_subdata`
* **BREAKING CHANGE** `mulle_range_min/mulle_range_max` renamed to `mulle_range_location_min` and `mulle_range_location_max,` `mulle_range_location_max,` for consistency with `INPTR_MIN/_MAX`
* **BREAKING CHANGE** `mulle_range_get_end` is now called `mulle_range_get_max,` `mulle_range_get_max` was renamed to `mulle_range_get_last_location.` This is for consistency with NSMaxRange(), otherwise it's just confusing
* **BREAKING CHANGE** `mulle_range_for` reverses the arguments, so the order is compatible with the `_for` macros of mulle-container
* added `mulle_range_for` convenience macro
* added `mulle_range_zero`
* added `mulle_range_insert`


### 0.2.1

* remove package.json as it conflicts with clib.json
* used `mulle_range_is_valid` in asserts in some functions, those have now underscore prefixed variants to skip the assert
* added functions `mulle_range_greater_than_location` for easier comparison coding in NSIndexSet

## 0.2.0

* new function `mulle_range_subtract`


## 0.1.0

* change some global declarations for windows
* new generic `mulle_hash` function for data
* new string hash function


### 0.0.3

* fix `mulle_float_hash`

### 0.0.2

* add struct `mulle_range`

### 0.0.1

* added mulle-fnv1a executable
* initial commit, files were split off from mulle-objc-runtime and mulle-container
