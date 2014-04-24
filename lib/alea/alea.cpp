#include <stdlib.h>
#include <assert.h>

int alea( int n )
{
 assert (0 < n && n <= RAND_MAX);
 int partSize = (RAND_MAX+1) / (n+1);
 int firstToBeDropped = partSize * (n+1);
 int draw;
 do {
   draw = rand();
 } while (draw >= firstToBeDropped);
 return draw % (n + 1);
}
