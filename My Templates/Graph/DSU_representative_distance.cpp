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
    pair<ll,ll> parent;
    ll rank;
};

void initialise(subset* s,ll n){
    REP(i,0,n){
        s[i].parent = {i,0};
        s[i].rank = 0;
    }
}

pair<ll,ll> find(ll v,subset* s){
    if(v != s[v].parent.first){
        ll len = s[v].parent.second;
        s[v].parent = find(s[v].parent.first,s);
        s[v].parent.second += len;
    }
    return s[v].parent;
}

void union_sets(ll x,ll y,subset* s){
    ll x = find(x,s).first;
    ll y = find(y,s).first;
    if(x != y){
        if(s[x].rank < s[y].rank)
            swap(x,y);
        s[y].parent = make_pair(x, 1);
        if(s[x].rank == s[y].rank)
            s[x].rank++;
    }
}

int main()
{
    // Maintain the distance between a vertex and the representative of its set 
    // (i.e. the path length in the tree from the current node to the root of the tree).
    // If we don't use path compression, the distance is just the number of recursive calls. But this will be inefficient.
    // However it is possible to do path compression, if we store the distance to the parent as additional information for each node.
    return 0;
}