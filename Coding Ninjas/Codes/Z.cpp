#include <bits/stdc++.h>
using namespace std;
void getprefix(int* Z,int n,string q){
	Z[0] = 0;
	int i = 1;
	int r = 0;
	int l = 0;
	while(i < n){
		if(i > r){
			 l = i;
			 r = i;
			 while(r < n && q[r]==q[r-l]){
			 	r++;
			 }
			 Z[i] = r - l;
			 r--;
		}
		else {
			if(Z[i-l] + i <=r){
				Z[i] = Z[i-l];
			}
			else {
				l = i;
				while(r < n && q[r]==q[r-l]){
					r++;
				}
				Z[i] = r - l;
				r--;
			}
		}
		i++;
	}
}
void zalgorithm(string S,string T){
	int t = T.size();
	string q = T + "$" + S;
	int* Z = new int[q.size()];
	getprefix(Z,q.size(),q);
	for(int i=0;i<q.size();i++){
		if(Z[i]==t){
			cout<<i-t-1<<" ";
		}
	}
}
int main()
{
	string S,T;
	getline(cin,S);
	getline(cin,T);
	zalgorithm(S,T);
	return 0;
}