#include <stdlib.h>
#include <assert.h>
int alea( int n )
{
 assert (0 < n && n <= RAND_MAX);
 unsigned int partSize = (RAND_MAX+1) / (n+1);
 unsigned int firstToBeDropped = partSize * (n+1);
 unsigned int draw;

 do {
   draw = rand();
 } while (draw >= firstToBeDropped);
 return draw % (n + 1);
}




