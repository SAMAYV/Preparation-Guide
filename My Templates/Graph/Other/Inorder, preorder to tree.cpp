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

ll construct(vector<ll>* edges,ll* preorder,ll l1,ll r1,ll* inorder,ll l2,ll r2,unordered_map<ll,ll>& umin,unordered_map<ll,ll>& umpre){
	if(r1 < l1 || r2 < l2){
		return -1;
	}
	if(r1 == l1){
		return preorder[l1];
	}
	else if(l2 == r2){
		return inorder[l2];
	}
	
	ll root = preorder[l1];
	ll val1 = umin[root];

	ll v1 = construct(edges,preorder,l1+1,l1+val1-l2,inorder,l2,val1-1,umin,umpre);
	ll v2 = construct(edges,preorder,l1+val1-l2+1,r1,inorder,val1+1,r2,umin,umpre);
	if(v1!=-1){
		edges[root].push_back(v1);	
		edges[v1].push_back(root);
	}
	if(v2!=-1){
		edges[root].push_back(v2);	
		edges[v2].push_back(root);
	}
	return root;
}
int main() 
{ 
	ll n;
	cin>>n;
	vector<ll> edges[n+1];
	ll* inorder = new ll[n];
	ll* preorder = new ll[n];
	unordered_map<ll,ll> umpre,umin;
	REP(i,0,n){
		cin>>preorder[i];
		umpre[preorder[i]] = i;
	}
	REP(i,0,n){
		cin>>inorder[i];
		umin[inorder[i]] = i;
	}
	construct(edges,preorder,0,n-1,inorder,0,n-1,umin,umpre);
	
	REP(i,1,n){
		cout<<endl;
		cout<<i<<": ";
		for(auto it:edges[i]){
			cout<<it<<" ";
		}
	}
	return 0;	
} 
