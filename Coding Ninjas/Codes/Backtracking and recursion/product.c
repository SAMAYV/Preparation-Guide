#include<stdio.h>
int N;
int b[4];
int issafe(int s,int k,int prd,int max)
{
   if(s<=N && k<=3 )
   	return 1;
   else return 0;
}
int product(int s,int n,int k,int p,int max,int* a)
{
	int sum;
	int prd;
	if(s==N && b[0]!=0 && b[1]!=0 && b[2]!=0 && b[3]!=0 && prd>=max)
	{
		max = prd;
		return 1;
  }
	for(int i=0;i<n;i++)
	{
		prd = p*a[i];
		sum = s + a[i];
		if(issafe(s,k,prd,max)==1)
		{
           b[k]=a[i];
           if(product(sum,n,k+1,prd,max,a)==1)
             return 1;
           b[k]=0;
		}
	}
	return 0;
}
int main()
{
	scanf("%d",&N);
	int a[N];
	int c=0;
	for(int i=0;i<4;i++)
      b[i]=0;

  for(int j=1;j<=N;j++)
    if(N%j==0)
    {	
      a[c]=j;
      c++;
    }
  //for(int i=0;i<N;i++)
    product(0,c,0,1,b[0]*b[1]*b[2]*b[3],a);
     //continue;
  for(int i=0;i<4;i++)
    printf("%d ",b[i]);

}
