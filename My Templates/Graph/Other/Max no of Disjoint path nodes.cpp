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

bool bfs(vector<ll>* edges,ll n,ll* parent,ll x,map<pair<ll,ll>,ll>& um,ll dest){
	queue<ll> q;
	bool visited[n];
	REP(i,0,n) visited[i] = 0;

	q.push(x);
	visited[x] = 1;
	parent[x] = x;

	while(q.size()){
		ll curr = q.front();
		q.pop();
		for(auto u : edges[curr]){
			if(visited[u] == 0 && um[{curr,u}] > 0){
				q.push(u);
				visited[u] = 1;
				parent[u] = curr;
			}
		}
	}
	return (visited[dest] == 1);
}

void fordfulkerson(vector<ll>* edges,ll n,map<pair<ll,ll>,ll>& um,ll e,ll x,ll dest){
	ll sum = 0;
	ll* parent = new ll[n];
	REP(i,0,n) parent[i] = -1;

	while(bfs(edges,n,parent,x,um,dest)){
		ll curr = dest;
		ll m = INT_MAX;
		while(parent[curr] != curr){
			m = min(m,um[{parent[curr],curr}]);
			curr = parent[curr];
		}
		sum += m;
		curr = dest;
		while(parent[curr] != curr){
			um[{parent[curr],curr}] -= m;
			curr = parent[curr];
		}
	}
	cout<<sum<<endl;
}
int main() 
{ 
	ll n,e;
	cin>>n>>e;
	vector<ll> edges[2*n];
	map<pair<ll,ll>,ll> um;

	ll source,dest;
	cin>>source>>dest;
	source--; dest--;

	REP(i,0,e){
		ll x,y;
		cin>>x>>y;
		x--; y--;
		if(x == source){
			edges[x].push_back(y);
			um[{x,y}] = 1;
		}
		else {
			edges[x+n].push_back(y);
			um[{x+n,y}] = 1;
		}
		if(y != dest){
			if(!um[{y,y+n}])
				edges[y].push_back(y+n);
			um[{y,y+n}] = 1;
		}
	}
	// REP(i,0,2*n){
	// 	cout<<i+1<<":";
	// 	for(auto it:edges[i]){
	// 		cout<<it+1<<" ";
	// 	}
	// 	cout<<endl;
	// }
	
	fordfulkerson(edges,2*n,um,e,source,dest);

	return 0;	
} 