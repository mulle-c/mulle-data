//
//  mulle-fnv1a.c
//  mulle-data
//
//  Created by Nat! on 19.08.17

/***
 *
 * Please do not copyright this code.  This code is in the public domain.
 *
 * LANDON CURT NOLL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL LANDON CURT NOLL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * By:
 *      chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 *
 * Share and Enjoy!     :-)
 */

#include "mulle-fnv1a.h"


uint32_t   _mulle_fnv1a_chained_32( void *buf, size_t len, uint32_t hash)
{
   return( _mulle_fnv1a_chained_32_inline( buf, len, hash));
}


uint64_t   _mulle_fnv1a_chained_64( void *buf, size_t len, uint64_t hash)
{
   return( _mulle_fnv1a_chained_64_inline( buf, len, hash));
}


// Build it with:
//
// cc -o mulle_objc_fnv1a -DMAIN mulle_fnv1a.c
// to check if it produces same results as reference implementation
//
#ifdef MAIN

#include <stdio.h>
#include <string.h>


int   main( int argc, char * argv[])
{
   if( argc < 2)
      return( -1);

   if( argc == 3)
   {
      switch( argv[ 2][ 1])
      {
      case '3' :
         printf( "0x%08lx\n", (unsigned long) _mulle_objc_fnv1a_32( argv[ 1], strlen( argv[ 1])));
         return( 0);

      case '6' :
         printf( "0x%08llx\n", (unsigned long long) _mulle_objc_fnv1a_64( argv[ 1], strlen( argv[ 1])));
         return( 0);
      }
   }

   printf( "0x%08llx\n", (unsigned long long) _mulle_objc_fnv1a( argv[ 1], strlen( argv[ 1])));
   return 0;
}

#endif
