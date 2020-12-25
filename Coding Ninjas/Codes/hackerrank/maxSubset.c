#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long maxSubsetSum(long arr_count, long* arr) {
    long d=2;
    long j=0;
    long s[10000];
  while(d<arr_count)
  {
   for(long i=0;i<arr_count;i=i+d)
   {
     if(arr[i]>0)
      s[j]=s[j]+arr[i];
   }
   j++;
   d++;
  }
  long e=2;
  while(e<arr_count-1)
  {
   for(long i=1;i<arr_count;i=i+e)
   {
       if(arr[i]>0)
        s[j]=s[j]+arr[i];
   }
   j++;
   e++;
  }
   long k=1;
   long max=s[0];
   while(s[k])
   {
       if(s[k]>max)
        max=s[k];
       k++;
   }
   return max;
}

int main()
{
    long n;
    scanf("%ld",&n);
    long a[n];
    for(long i=0;i<n;i++)
     scanf("%ld",&a[i]);
    printf("%ld",maxSubsetSum(n,a));
    return 0;
}


 
