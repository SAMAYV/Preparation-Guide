#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Complete the superDigit function below.
char* superDigit(char* n, int k) {
  if(strlen(n)==1)
    return n;
  else
  {
      int s=0;
      int i=0;
      while(n[i]!='\0')
      { 
          s=s+(int)n[i];
          n[i]='\0';
          i++;
      }
      //s=s*k;
      int temp=s;
      int c=0;
      while(temp)
      {
        c++;
        temp=temp/10;
      }
      temp=s;
      int j=0;
      while(temp)
      {
          n[c-1-j]=s%10;
          temp=temp/10;
          j++;
      }
     return superDigit(n,1);
  }

}

int main()
{
    char n[100];
    int k;
    scanf("%s%d",n,&k);
    printf("%s",superDigit(n,k));
    return 0;
}
