#include <stdio.h>
int a[10][10];
int N;
int position(int l,int m)
{
    if(l>=0 && m>=0 && l<10 && m<10)
      return 1;
    else return 0;
}
int knight(int* movex,int* movey,int i,int j,int n)
{
    if(n==N && a[i][j]!=1)
     return 1;
    int l,m;
    for(int k=0;k<8;k++)
    {
        l = i + movex[k];
        m = j + movey[k];
        if(position(l,m)==1)
        {
            if(knight(movex,movey,l,m,n+1)==1)
            {    a[l][m]=1;
            }
        }
    }
    return 0;
}
int main()
{
    int i,j;
    int c=0;
    scanf("%d %d %d",&i,&j,&N);
    int movex[8] = {1,-1,1,-1,2,2,-2,-2};
    int movey[8] = {2,2,-2,-2,1,-1,1,-1};
    if(knight(movex,movey,i-1,j-1,0)==0)
      for(int i=0;i<10;i++)
       for(int j=0;j<10;j++)
        if(a[i][j]==1)
         c++;
    printf("%d",c);   
}
