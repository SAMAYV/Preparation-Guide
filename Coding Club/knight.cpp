#include<bits/stdc++.h>
#include<time.h>
using namespace std;

int boolean(int l,int m,int** a,int N)
{
	return (l<N && l>=0 && m<N && m>=0 && a[l][m]==-1);
}

int place(int i,int j,int* nextx,int* nexty,int c,int** a,int N)
{
    int l,m;
    if(c==N*N)
    	return 1;
    for(int k=0;k<8;k++)
    {
    	l=i+nextx[k];
    	m=j+nexty[k];
    	if(boolean(l,m,a,N)==1)
    	{
        	a[l][m]=c;
            if(place(l,m,nextx,nexty,c+1,a,N)==1)
            	return 1;
            else a[l][m]=-1;
        }
    }
    return 0;	
}
void knight(int** a,int N)
{
	int nextx[8] = {  2, 1, -1, -2, -2, -1,  1,  2 }; 
	int nexty[8] = {  1, 2,  2,  1, -1, -2, -2, -1 }; 
	a[0][0]=0;
    if(place(0,0,nextx,nexty,1,a,N))
      for(int i=0;i<N;i++){
          for(int j=0;j<N;j++)
            cout<<a[i][j]<<" ";
          cout<<endl;
       }
    else 
    	cout<<"Not Possible"<<endl;
}
int main()
{
	time_t clock(void);
	clock_t timetaken;
	int N;
	cin>>N;
    int** a = new int*[N];
    for(int i=0;i<N;i++)
  		a[i] = new int[N];

    for(int i=0;i<N;i++)
    	for(int j=0;j<N;j++)
        	a[i][j]=-1;

    timetaken = clock();
    knight(a,N);
    timetaken = clock() - timetaken;
    double diff = (double)timetaken/CLOCKS_PER_SEC;
    cout<<diff<<endl;
    return 0;
}