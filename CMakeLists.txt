cmake_minimum_required( VERSION 3.14)

project( mulle-data VERSION 0.3.2 LANGUAGES C)


#
# Turn a "Library" into an "Executable"
# * touch src/main.m
# Then set MULLE_PROJECT_TYPE to "Executable".
# * mulle-sde reflect
# * mulle-sde craft
#
set( MULLE_PROJECT_TYPE "Library")

### mulle-sde environment

# add cmake module paths to search path
list( INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/share")
list( INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/reflect")
list( INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include( Environment)
include( Files)

### Library

if( HEADERS_PHASE)
   install( FILES ${INSTALL_PUBLIC_HEADERS}  DESTINATION "include/${PROJECT_NAME}")
   install( FILES ${INSTALL_PRIVATE_HEADERS} DESTINATION "include/${PROJECT_NAME}")
   install( FILES ${INSTALL_CMAKE_INCLUDES}  DESTINATION "include/${PROJECT_NAME}/cmake")

   # short cut out
   if( NOT COMPILE_PHASE AND NOT LINK_PHASE)
      return()
   endif()
endif()

if( LINK_PHASE)
   include( Dependencies OPTIONAL)
endif()

include( Library)

# use LIBRARY_COMPILE_TARGET for compiler options
target_compile_definitions( "${LIBRARY_COMPILE_TARGET}" PUBLIC)
target_compile_options( "${LIBRARY_COMPILE_TARGET}" PUBLIC)
if( NOT MSVC)
   target_compile_options( "${LIBRARY_COMPILE_TARGET}" PUBLIC -Wunused)
endif()

# use LIBRARY_LINK_TARGET for linker options
if( LINK_PHASE)
   target_link_options( "${LIBRARY_LINK_TARGET}" PUBLIC)
endif()

include( InstallLibrary)


if( LINK_PHASE)
   include( InstallCMakeInclude)
   include( InstallCMakePackage)
endif()


### --------------------------------------------------------

set( EXECUTABLE_NAME mulle-fnv1a)

# only need the hash function (done like this if runtime is built as shared)
set( EXECUTABLE_SOURCES  ${MULLE_FNVA1_NO_CLIB})

set( EXECUTABLE_DEPENDENCY_NAMES "mulle-data")

# only need the hash function
set( EXECUTABLE_LIBRARY_LIST "mulle-data")

include( Executable)

# use LIBRARY_COMPILE_TARGET for compiler options
target_compile_definitions( "${EXECUTABLE_COMPILE_TARGET}" PUBLIC)
target_compile_options( "${EXECUTABLE_COMPILE_TARGET}" PUBLIC)
# use LIBRARY_LINK_TARGET for linker options
if( LINK_PHASE)
   target_link_options( "${EXECUTABLE_LINK_TARGET}" PUBLIC)
endif()

include( InstallExecutable)


include( FinalOutput OPTIONAL)
