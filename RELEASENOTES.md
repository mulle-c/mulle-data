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
