#include "../inc/utility.h"

int range_random(int min, int max)
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); 
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

