#include <bits/stdc++.h>
using namespace std;
bool isvalid(char** G,int n,int m,int sx,int sy,bool** visited){
	if(sx < 0 || sx >=n || sy < 0 || sy >=m)
		return false;
	if(visited[sx][sy]==true)
		return false;
	return true;
}
int connecting(char** G,int n,int m,bool** visited,int sx,int sy,int i,int j){
	visited[sx][sy] = true;
	int xv[4] = {0,1,0,-1};
	int yv[4] = {1,0,-1,0};
	for(int k=0;k<4;k++){
		if(isvalid(G,n,m,sx+xv[k],sy+yv[k],visited) && G[sx][sy]==G[sx+xv[k]][sy+yv[k]]){
			// cout<<sx<<" "<<sy<<endl;
			int count = connecting(G,n,m,visited,sx+xv[k],sy+yv[k],i,j);
			// cout<<count<<endl;
			if(count!=-1){
				visited[sx][sy] = false;
				return count + 1;
			}
		}
	}
	if(sx-1==i && sy==j){
		// cout<<sx<<" "<<sy<<endl;
		visited[sx][sy] = false;
		return 1;
	}

	visited[sx][sy] = false;
	return -1;
}
bool dots(char** G,int n,int m){
	bool** visited = new bool*[n];
	for(int i=0;i<n;i++){
		visited[i] = new bool[m];
		for(int j=0;j<m;j++)
			visited[i][j] = false;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int x = connecting(G,n,m,visited,i,j,i,j);
			// for(int i=0;i<n;i++){
			// 	// G[i] = new char[m];
			// 	for(int j=0;j<m;j++)
			// 		if(!visited[i][j])
			// 			cout<<0<<" ";
			// 		else
			// 			cout<<1<<" ";
			// 	cout<<endl;
			// }
			// cout<<endl;
			if(x>=4)
				return true;
		}
	}
	return false;
}
int main()
{
	int n,m;
	cin>>n>>m;
	char** G = new char*[n];
	for(int i=0;i<n;i++){
		G[i] = new char[m];
		for(int j=0;j<m;j++)
			cin>>G[i][j];
	}
	// int x = dots(G,n,m);
	// cout<<x<<endl;
	if(dots(G,n,m))
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
}