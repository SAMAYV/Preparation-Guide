#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i,f,n) for(int i=0;i<n;i+=f) 
void fill(int** a,int value,char seq,int posx,int posy,int n){
	a[posx][posy] = value;
	if(value==n*n){
		return;
	}
	if(seq=='R'){
		if(posy+1 < n && a[posx][posy+1]==0)
			fill(a,value+1,'R',posx,posy+1,n);
		else if(posx+1 < n && a[posx+1][posy]==0)
			fill(a,value+1,'D',posx+1,posy,n);
		else 
			return;
	}
	else if(seq=='D'){
		if(posx+1 < n && a[posx+1][posy]==0)
			fill(a,value+1,'D',posx+1,posy,n);
		else if(posy-1 >= 0 && a[posx][posy-1]==0)
			fill(a,value+1,'L',posx,posy-1,n);
		else 
			return;
	}
	else if(seq=='L'){
		if(posy-1 >= 0 && a[posx][posy-1]==0)
			fill(a,value+1,'L',posx,posy-1,n);
		else if(posx-1 >= 0 && a[posx-1][posy]==0)
			fill(a,value+1,'U',posx-1,posy,n);
		else 
			return;
	}
	else if(seq=='U'){
		if(posx-1 >= 0 && a[posx-1][posy]==0)
			fill(a,value+1,'U',posx-1,posy,n);
		else if(posy+1 < n && a[posx][posy+1]==0)
			fill(a,value+1,'R',posx,posy+1,n);
		else 
			return;
	}
}
int main()
{
	int n;
	cin>>n;
	int** a = new int*[n];
	REP(i,1,n){
		a[i] = new int[n]();
	}
	fill(a,1,'R',0,0,n);
	REP(i,1,n){
		REP(j,1,n){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}