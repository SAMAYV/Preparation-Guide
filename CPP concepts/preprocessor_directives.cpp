#include<iostream>
 
#define gfg 7
  
#if gfg > 200
   #undef gfg
   #define gfg 200
#elif gfg < 50
   #undef gfg
   #define gfg 50
#else
   #undef gfg
   #define gfg 100
#endif

#ifndef GeeksforGeeks
#error GeeksforGeeks not found !
#endif 
 
int main()
{
    std::cout << gfg;  // gfg = 50
}  