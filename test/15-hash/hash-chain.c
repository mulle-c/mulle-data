#include <mulle-data/mulle-data.h>
#include <stdio.h>


int   main( void)
{
   uintptr_t  hash;
   void       *state;

   // leftovers
   hash = _mulle_hash_32( "VfL Bochum 1848", 15);
   printf( "32: %#016tx\n", hash);

   hash = _mulle_hash_64( "VfL Bochum 1848", 15);
   printf( "64: %#016tx\n", hash);

   // these hash values must be identical to above, otherwise chaining
   // is broken
   state = NULL;
          mulle_hash_chained_32( "VfL Bochum", 10, &state);
          mulle_hash_chained_32( " 1848", 5, &state);
   hash = mulle_hash_chained_32( NULL, 0, &state);
   printf( "chain32: %#016tx\n", hash);

   state = NULL;
          mulle_hash_chained_64( "VfL Bochum", 10, &state);
          mulle_hash_chained_64( " 1848", 5, &state);
   hash = mulle_hash_chained_64( NULL, 0, &state);
   printf( "chain64: %#016tx\n", hash);

   return( 0);
}
