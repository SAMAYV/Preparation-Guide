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

ll timer = 1, SCC = 0;
vector<bool> vis,onStack;
vector<ll> in,low;
stack<ll> st;

void dfs(ll node,vector<ll>* edges)
{
    vis[node] = 1;
    in[node] = low[node] = timer++;
    onStack[node] = 1;
    st.push(node);
    for(auto u:edges[node]){
        if(vis[u] && onStack[u]){
            low[node] = min(low[node],in[u]);
        }
        else {
            if(!vis[u]){
                dfs(u,edges);
                if(onStack[u]){
                    low[node] = min(low[node],low[u]);       
                } 
            }
        }
    }
    if(in[node] == low[node]){
        SCC++;
        cout<<"SCC #"<<SCC<<endl;
        while(st.size() && st.top() != node){
            ll u = st.top();
            st.pop(); 
            onStack[u] = 0;
            cout<<u<<" ";
        }
        cout<<endl;
    }
}

void tarjan(ll n,vector<ll>* edges){
    timer = 1;
    SCC = 0;
    vis.resize(n,0);
    onStack.resize(n,0);
    in.resize(n,0);
    low.resize(n,0);
    REP(i,0,n){
        if(!vis[i]) dfs(i,edges);
    }
}

int main() 
{
    
    return 0; 
}
 