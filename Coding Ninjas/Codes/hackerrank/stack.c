#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int a[10000];
int top=-1;
void push(int item);
void pop();
int max();
int main(void) {
    int n;
    int value;
    int k=0;
    int long b[1000];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
      scanf("%d",&value);
      if(value==1)
      {
          int long item;
          scanf("%ld",&item);
          push(item);
      }
      else if(value==2)
       pop();
      else if(value==3)
      {
         b[k]=max();
         k++;
      }
    }
    for(int i=0;i<k;i++)
     printf("%ld\n",b[i]);
    return 0;
}
void push(int item)
{
    top++;
    a[top]=item;
}
void pop()
{
   top--;
}
int max()
{
    int max=a[0];
    for(int i=1;i<=top;i++)
    {
        if(a[i]>max)
         max=a[i];
    }
    return max;
}

