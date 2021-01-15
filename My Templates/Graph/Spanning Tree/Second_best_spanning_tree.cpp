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
    ll s, e, w, id;
    bool operator<(const struct Edge& other){return w < other.w;}
};
struct subset {
    int rank;
    int parent;
};
int find(int x,subset* s){
    if(s[x].parent==x)
        return x;
    s[x].parent = find(s[x].parent,s);
    return s[x].parent;
}
void unio(int x,int y,subset* s){
    int p1 = find(x,s);
    int p2 = find(y,s);
    if(s[p1].rank == s[p2].rank){
        s[p1].rank++;
        s[p2].parent = p1;
    }
    else if(s[p1].rank > s[p2].rank){
        s[p2].parent = p1;
    }
    else {
        s[p1].parent = p2;  
    }
}

ll res = 0, l = 21;
vector<Edge> edges;
vector<ll> h, parent, size, present;
vector<vector<pair<ll,ll>>> adj,dp;
vector<vector<ll>> up;

pair<ll,ll> combine(pair<ll,ll> a, pair<ll,ll> b){
    vector<ll> v = {a.first, a.second, b.first, b.second};
    ll topTwo = -3, topOne = -2;
    for(ll c : v){
        if(c > topOne){
            topTwo = topOne;
            topOne = c;
        } 
        else if (c > topTwo && c < topOne){
            topTwo = c;
        }
    }
    return {topOne,topTwo};
}
void dfs(ll u,ll par,ll d){
    h[u] = 1 + h[par];
    up[u][0] = par;
    dp[u][0] = {d, -1};
    for(auto v : adj[u]){
        if(v.first != par){
            dfs(v.first, u, v.second);
        }
    }
}
pair<ll,ll> lca(ll u,ll v){
    pair<ll,ll> ans = {-2,-3};
    if(h[u] < h[v]){
        swap(u, v);
    }
    REPI(i,0,l){
        if(h[u] - h[v] >= (1 << i)){
            ans = combine(ans, dp[u][i]);
            u = up[u][i];
        }
    }
    if(u == v){
        return ans;
    }
    REPI(i,0,l){
        if(up[u][i] != -1 && up[v][i] != -1 && up[u][i] != up[v][i]){
            ans = combine(ans, combine(dp[u][i], dp[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }
    ans = combine(ans,combine(dp[u][0],dp[v][0]));
    return ans;
}
void intitialise(ll n){
    parent.resize(n+1);
    REP(i,1,n+1){
        parent[i] = i;
    }
    size.resize(n+1,1);
    up.resize(n+1,vector<ll>(l,-1));
    dp.resize(n+1,vector<pair<ll,ll>>(l));
    h.resize(n+1,0);
    present.resize(n+1,0);
    adj.resize(n+1,vector<pair<ll,ll>>());
}
ll Kruskal(ll n,ll m){
    subset s[n];
    REP(i,0,n){
        s[i].rank = 0;
        s[i].parent = i;
    }
    ll res = 0;
    sort(edges.begin(),edges.end());
    REP(i,0,m){
        ll a = edges[i].s;
        ll b = edges[i].e;
        ll w = edges[i].w;
        ll id = edges[i].id;
        if(find(a,s) != find(b,s)){
            unio(a,b,s); 
            adj[a].push_back({b,w});
            adj[b].push_back({a,w});
            present[id] = 1;
            res += w;
        }
    }
    return res;
}
void LCA_spanning_tree(ll n){
    REP(i,1,l){
        REP(j,1,n+1){
            if(up[j][i - 1] != -1){
                ll v = up[j][i - 1];
                up[j][i] = up[v][i - 1];
                dp[j][i] = combine(dp[j][i - 1], dp[v][i - 1]);
            }
        }
    }
}
ll second_best_spanning_tree(ll m,ll res){
    ll ans = 1e18;
    REP(i,0,m){
        ll id = edges[i].id;
        ll w = edges[i].w;
        if(!present[id]){
            auto rem = lca(edges[i].s, edges[i].e);
            if(rem.first != w){
                if(ans > res + w - rem.first){
                    ans = res + w - rem.first;
                }
            } 
            else if(rem.second != -1){
                if(ans > res + w - rem.second){
                    ans = res + w - rem.second;
                }
            }
        }
    }
    return ans;
}
int main(void) 
{
    ll n,m;
    cin>>n>>m;
    intitialise(n);
    REP(i,0,m){
        ll a,b,w;
        cin>>a>>b>>w; // 1-indexed
        edges.push_back({a,b,w,i});
    }
    ll res = Kruskal(n,m);
    dfs(1, 0, 0);
    LCA_spanning_tree(n);
    ll ans = second_best_spanning_tree(m,res);
    cout<<ans<<"\n";
    return 0;
}