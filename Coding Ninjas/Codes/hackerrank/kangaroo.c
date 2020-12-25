#include<stdio.h>
int main()
{
    long x1,v1,x2,v2;
    scanf("%ld %ld %ld %ld",&x1,&v1,&x2,&v2);
    long d1,d2;
    long i=0;
    long j=0;
    d1=x1+(v1*i);
    d2=x2+(v2*j);
    while(d1!=d2)
    {    if((x2>x1)&&(v2>v1))
          printf("NO");
        if((x2<x1)&&(v2<v1))
          printf("NO");
         while(d1<d2)
          i++;
         while(d2<d1)
          j++;  
    }
  if(d1==d2)
   printf("YES");
  else printf("NO");
}
