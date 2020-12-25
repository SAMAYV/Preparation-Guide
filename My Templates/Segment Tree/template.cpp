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
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set1;
typedef tree<string,null_type,less<string>,rb_tree_tag,tree_order_statistics_node_update> indexed_set2;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

void buildtree(ll tree[],ll start,ll end,ll treenode,ll arr[]){
    if(start == end){
        tree[treenode] = arr[start];
        return;
    }
    ll mid = (start+end)/2;
    buildtree(tree,start,mid,2*treenode,arr);
    buildtree(tree,mid+1,end,2*treenode+1,arr);
    tree[treenode] = min(tree[2*treenode],tree[2*treenode+1]);
}
void update(ll tree[],ll start,ll end,ll treenode,ll ind,ll val){
    if(ind < start || ind > end){
        return;
    }
    if(start == end){
        tree[treenode] = val;
        return;
    }
    ll mid = (start + end)/2;
    update(tree,start,mid,2*treenode,ind,val);
    update(tree,mid+1,end,2*treenode+1,ind,val);
    tree[treenode] = min(tree[2*treenode],tree[2*treenode+1]);    
}

// left to right which is required range
ll query(ll tree[],ll start,ll end,ll left,ll right,ll treenode){
    if(right < start || end < left){
        return 1e9;
    }
    if(left <= start && right >= end){
        return tree[treenode];
    }
    ll mid = (start + end)/2;
    ll q1 = query(tree,start,mid,left,right,2*treenode);
    ll q2 = query(tree,mid+1,end,left,right,2*treenode+1);
    return min(q1,q2);    
}
int main() 
{

	return 0;
}