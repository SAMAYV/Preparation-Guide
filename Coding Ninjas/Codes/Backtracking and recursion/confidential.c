#include<stdio.h>
#include<string.h>
void string(int u,int n,int p,char* a,char* b)
{
    if((n-u)!=0)
    {
        b[p]=a[(n+u)/2];
        string(u, (n+u)/2 -1, p+1, a, b);
        string((n+u)/2 +1 , n, p+1, a, b);
    }
    else if((n-u)==0)
    {
        b[p]=a[n];
    }
    else if((n-u)==0 && n==strlen(a)-1)
    {
        b[p]=a[n];
        printf("%s",b);
    }
}
int main()
{
    int t,l;
    int k=0;
    char a[10000];
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {
        scanf("%d",&l);
        char b[l];
        scanf("%s",a);
        string(0, l-1, k, a, b);
        
    }
}
