#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

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
// SOME BITMASK KNOWLEDGE
// 1)x & (x - 1):sets the last one bit of x to zero
// power of two exactly when x & (x − 1) = 0.
// 2)x & -x:sets all the one bits to zero, except last one bit
// 3)x | (x - 1):inverts all the bits after the last one bit
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set1;
typedef tree<string,null_type,less<string>,rb_tree_tag,tree_order_statistics_node_update> indexed_set2;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);

ll power(ll a,ll n,ll c){
    if(n == 0) return 1 % c;
    ll s = power(a,n/2,c);
    s = (s * s) % c;
    if(n % 2) s = (s * a) % c;
    return s;
}

vector<bool> visited;
vector<ll> tin, low;
ll timer = 0;

void dfs(ll v,vector<ll>* edges,ll p = -1){
    visited[v] = 1;
    tin[v] = low[v] = timer++;
    for(auto to:edges[v]){
        if(to == p) continue;
        if(visited[to]){
            low[v] = min(low[v], tin[to]);
        } 
        else {
            dfs(to,edges,v);
            low[v] = min(low[v], low[to]);
            if(low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}

void find_bridges(ll n,vector<ll>* edges){
    timer = 0;
    visited.assign(n,0);
    tin.assign(n,-1);
    low.assign(n,-1);
    REP(i,0,n){
        if(!visited[i])
            dfs(i,edges);
    }
}

// Function IS_BRIDGE(a, b) is some function that will process the fact that edge (a,b) is a bridge, for example, print it.
// Note that this implementation malfunctions if the graph has multiple edges, since it ignores them. 
// Of course, multiple edges will never be a part of the answer, so IS_BRIDGE can check additionally that the reported bridge is not a multiple edge. 
// Alternatively it's possible to pass to dfs the index of the edge used to enter the vertex instead of the parent vertex (and store the indices of all vertices).
// Now, there is a back edge from vertex v or one of its descendants to one of its ancestors if and only if vertex v has a child to for which low[to] ≤ tin[v]. 
// If low[to] = tin[v], the back edge comes directly to v, otherwise it comes to one of the ancestors of v.
// Thus, the current edge (v,to) in the DFS tree is a bridge if and only if low[to] > tin[v].

int main() 
{

    return 0; 
}
 