#include <mulle-data/mulle-data.h>
#include <stdio.h>


int   main( void)
{
   uintptr_t  hash;

   hash = mulle_hash( NULL, 0);
   printf( "0x%016tx\n", hash);

   hash = mulle_hash( "VfL Bochum 1848", 15);
   printf( "data: %#016tx\n", hash);

   hash = mulle_integer_hash( 1848);
   printf( "integer: %#016tx\n", hash);

   hash = mulle_long_long_hash( 1848);
   printf( "long long %#016tx\n", hash);

   hash = mulle_float_hash( 1848.0);
   printf( "float %#016tx\n", hash);

   hash = mulle_double_hash( 1848.0);
   printf( "double: %#016tx\n", hash);

   hash = mulle_pointer_hash( (void *) 1848);
   printf( "pointer: %#016tx\n", hash);

   // leftovers
   hash = _mulle_hash_32( "VfL Bochum 1848", 15);
   printf( "32: %#016tx\n", hash);

   hash = _mulle_hash_64( "VfL Bochum 1848", 15);
   printf( "64: %#016tx\n", hash);

   hash = _mulle_hash_chained_32( "VfL Bochum 1848", 15, 0);
   printf( "chain32: %#016tx\n", hash);

   hash = _mulle_hash_chained_64( "VfL Bochum 1848", 15, 0);
   printf( "hash32: %#016tx\n", hash);

   return( 0);
}