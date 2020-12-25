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

struct Edge {
    int a, b, cost;
};

void negative_cycle(ll n,ll m,vector<Edge> edges)
{
    vector<ll> dis(n);
    vector<ll> par(n,-1);
    ll x;
    REP(i,0,n){
        x = -1;
        for(Edge e : edges){
            if(dis[e.a] + e.cost < dis[e.b]){
                dis[e.b] = dis[e.a] + e.cost;
                par[e.b] = e.a;
                x = e.b;
            }
        }
    }
    if(x == -1){
        cout<<"No negative cycle found"<<endl;
    } 
    else {
        REP(i,0,n){
            x = par[x];
        }
        vector<ll> cycle;
        for(ll v = x;; v = par[v]){
            cycle.push_back(v);
            if(v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(),cycle.end());
        cout<<"Negative cycle: "<<endl;
        for(auto v : cycle) cout<<v<<" ";
        cout<<endl;
    }
}

int main() 
{

    return 0; 
}
 