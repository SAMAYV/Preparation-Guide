#include <bits/stdc++.h>
using namespace std;
void floyd(long** G,int V,int E){
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			cout<<G[i][j]<<" ";
		}
		cout<<endl;
	}
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			for(int k=0;k<V;k++){
				if(i!=j && j!=k){
					G[i][j] = min(G[i][j],G[i][k] + G[k][j]);
				}
			}
		}
	}
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			cout<<G[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main()
{
	int V,E;
	cin>>V>>E;
	long** G = new long*[V];
	for(int i=0;i<V;i++)
		G[i] = new long[V];

	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			G[i][j] = INT_MAX;
		}
	}
	for(int i=0;i<V;i++)
		G[i][i] = 0;
	for(int i=0;i<E;i++){
		int x,y,z;
		cin>>x>>y>>z;
		G[x][y] = z;
	}
	floyd(G,V,E);
}