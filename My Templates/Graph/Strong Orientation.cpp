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

vector<ll> tin,low;
ll bridge_cnt,timer;
string orient;
vector<bool> edge_used;

void find_bridges(ll v,vector<pair<ll,ll>>* adj,vector<pair<ll,ll>>& edges)
{
    low[v] = tin[v] = timer++;
    for(auto p : adj[v]){
        if(edge_used[p.second]) 
            continue;
        edge_used[p.second] = 1;
        orient[p.second] = ((v == edges[p.second].first) ? '>' : '<');
        ll nv = p.first;
        if(tin[nv] == -1){ 
            // if nv is not visited yet
            find_bridges(nv,adj,edges);
            low[v] = min(low[v],low[nv]);
            if(low[nv] > tin[v]){
                // a bridge between v and nv
                bridge_cnt++;
            }
        } 
        else {
            low[v] = min(low[v], tin[nv]);
        }
    }
}

void strong_orientation(ll n,ll m,vector<pair<ll,ll>>* adj,vector<pair<ll,ll>>& edges){
    timer = 0;
    bridge_cnt = 0;
    tin.resize(n,-1);
    low.resize(n,-1);
    orient.resize(m);
    edge_used.resize(n,0);
    ll comp_cnt = 0;
    REP(i,0,n){
        if(tin[i] == -1){
            comp_cnt++;
            find_bridges(i,adj,edges);
        }
    }
    printf("%lld\n%s\n", comp_cnt + bridge_cnt, orient.c_str());
}
int main() 
{
    ll n,m;
    cin>>n>>m;
    vector<pair<ll,ll>> adj[n];
    vector<pair<ll,ll>> edges(m);
    REP(i,0,m){
        ll a,b;
        cin>>a>>b;
        a--; b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        edges[i] = {a,b};
    }
    strong_orientation(n,m,adj,edges);
    return 0;
}