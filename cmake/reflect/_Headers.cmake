# This file will be regenerated by `mulle-match-to-cmake` via
# `mulle-sde reflect` and any edits will be lost.
#
# This file will be included by cmake/share/Headers.cmake
#
if( MULLE_TRACE_INCLUDE)
   MESSAGE( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

#
# contents are derived from the file locations

set( INCLUDE_DIRS
src
src/farmhash
src/reflect
)

#
# contents selected with patternfile ??-header--private-generated-headers
#
set( PRIVATE_GENERATED_HEADERS
src/reflect/_mulle-data-include-private.h
)

#
# contents selected with patternfile ??-header--private-generic-headers
#
set( PRIVATE_GENERIC_HEADERS
src/include-private.h
)

#
# contents selected with patternfile ??-header--private-headers
#
set( PRIVATE_HEADERS
src/farmhash/farmhash.h
src/farmhash/largeint.h
)

#
# contents selected with patternfile ??-header--public-generated-headers
#
set( PUBLIC_GENERATED_HEADERS
src/reflect/_mulle-data-include.h
src/reflect/_mulle-data-provide.h
)

#
# contents selected with patternfile ??-header--public-generic-headers
#
set( PUBLIC_GENERIC_HEADERS
src/include.h
)

#
# contents selected with patternfile ??-header--public-headers
#
set( PUBLIC_HEADERS
src/mulle-data.h
src/mulle-fnv1a.h
src/mulle-hash.h
src/mulle-prime.h
src/mulle-range.h
)

