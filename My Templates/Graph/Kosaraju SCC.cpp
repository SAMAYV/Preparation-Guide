#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long 
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
#define MAX 1e6
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

void dfs1(ll ind,vector<bool>& visited,stack<ll>& s,vector<ll>* edges){
	visited[ind] = 1;
	for(auto it:edges[ind]){
		if(!visited[it]){
			dfs1(it,visited,s,edges);
		}
	}
	s.push(ind);
}

void dfs2(ll ind,vector<bool>& visited,vector<ll>* edges,vector<ll>& v){
	visited[ind] = 1;
	v.push_back(ind);
	for(auto it:edges[ind]){
		if(!visited[it]){
			dfs2(it,visited,edges,v);
		}
	}
}

vector<vector<ll>> KosaRaju(vector<ll>* edges,vector<ll>* edgesT,ll n){
	vector<vector<ll>> components;
	stack<ll> s;
	vector<bool> visited(n,0);
	REP(i,0,n){
		if(!visited[i]){
			dfs1(i,visited,s,edges);
		}
	}
	vector<bool> visited2(n,0);
	while(s.size()){
		vector<ll> v;
		dfs2(s.top(),visited2,edgesT,v);
		components.push_back(v);
		s.pop();
		while(s.size() > 0 && visited2[s.top()] == 1){
			s.pop();
		}
	}
	return components;
}
int main() 
{ 
	ll v,e;
	cin>>v>>e;
	vector<ll> edges[v],edgesT[v];
	REP(i,0,e){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edgesT[y-1].push_back(x-1);
	}
	vector<vector<ll>> components = KosaRaju(edges,edgesT,v);  
	return 0;	
} 
