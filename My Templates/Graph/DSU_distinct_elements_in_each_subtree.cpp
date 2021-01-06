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
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

struct subset {
    ll parent;
};
void initialise(set<ll>* lst,subset* s,ll n,vector<ll>& values) {
    REP(i,0,n){
        lst[i].insert(values[i]);
        s[i].parent = i;
    }
}
ll find(ll x,subset* s){
    if(s[x].parent == x)
        return x;
    s[x].parent = find(s[x].parent,s);
    return s[x].parent;
}
void unio(ll a,ll b,subset* s,set<ll>* lst){
    a = find(a,s);
    b = find(b,s);
    if(a != b){
        if(lst[a].size() < lst[b].size()){
            swap(a, b);
        }
        while(lst[b].size()){
            ll v = *lst[b].begin();
            lst[b].erase(lst[b].begin());
            s[v].parent = a;
            lst[a].insert(v);
        }
    }
}
void dfs(ll curr,ll par,subset* s,set<ll>* lst,vector<ll>& answer,vector<ll>& values){
    for(auto it:edges[curr]){
        if(it != par){
            dfs(it,curr,s,lst,answer,values);
            unio(curr,it,s,lst);
        }
    }
    answer[curr] = lst[find(curr,s)].size();
}
void distinct_ele_in_each_subtree(vector<ll>* edges,ll n,vector<ll>& values){
    set<ll> lst[n];
    subset s[n];
    initialise(lst,s,n,values);
    vector<ll> answer(n,0);
    dfs(0,-1,s,lst,answer,values);
}
int main()
{
    // we are given a tree, each leaf has a number assigned (same number can appear multiple times on different leaves). 
    // We want to compute the number of different numbers in the subtree for every node of the tree.
    ll n;
    cin>>n;
    vector<ll> edges[n];
    vector<ll> values(n);
    distinct_ele_in_each_subtree(edges,n,values);
    return 0;
}