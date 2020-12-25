#include<stdio.h>
int N;
int issafe()
{

}
int forest(a,i,j,nx,ny,c)
{
	int l,m;
   for(int k=0;k<4;k++)
   {
   	l = i + nx[k];
   	m = j + ny[k];
   	if(issafe(l,m))
   	{
   		a[l][m]= c;
   		c = char(int(c)+1);
        if(forest()==1)
        	
   	}
   }
   return 0;
}
int water(a)
{

	int i,j;
	int nx[4] = {1,-1,0,0};
	int ny[4] = {0,,0,1,-1};
   for(i=0;i<N;i++)
    {
     for(j=0;j<N;j++)
      {	
      	while(a[i][j]!='T')
     		j++;
     	if(a[i][j]=='T')
     		break;
       }
     if(a[i][j]=='T')
     	break;
    }

   if(a[i][j]=='T')
   	{
       forest(a,i,j,nx,ny,'1');
       water(a);
   	}
   	else {
   		return 1;
   	} 

} 
int main()
{
	scanf("%d",&N);
	char a[N][N];
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++)
	  	scanf("%c ",&a[i][j]);
    

}