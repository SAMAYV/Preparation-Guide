#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
#define ll long long int
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
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
struct lazy1 {
	ll val;
	ll add;
};
struct tree1 {
	ll sum;
	ll sos;
};
void buildtree(tree1* tree,ll left,ll right,ll treeNode,ll* arr){
	if(left == right){
		tree[treeNode].sum = arr[left];
		tree[treeNode].sos = arr[left]*arr[left];
		return;
	}
	ll mid = (left + right)/2;
	buildtree(tree,left,mid,2*treeNode,arr);
	buildtree(tree,mid+1,right,2*treeNode+1,arr);
	tree[treeNode].sum = tree[2*treeNode].sum + tree[2*treeNode+1].sum;
	tree[treeNode].sos = tree[2*treeNode].sos + tree[2*treeNode+1].sos;
}
void lazytree(tree1* tree,lazy1* lazy,ll start,ll end,ll treeNode){
	if(lazy[treeNode].add != 0){
		if(lazy[treeNode].val == 1){
			tree[treeNode].sos += (end-start+1) * lazy[treeNode].add * lazy[treeNode].add + 2*tree[treeNode].sum * lazy[treeNode].add;
			tree[treeNode].sum += (end-start+1) * lazy[treeNode].add;
			if(start != end){
				lazy[2*treeNode].add += lazy[treeNode].add;
				lazy[2*treeNode+1].add += lazy[treeNode].add;
				if(lazy[2*treeNode].val == 2)
					lazy[2*treeNode].val = 1;
				if(lazy[2*treeNode+1].val == 2)
					lazy[2*treeNode+1].val = 1;
			}
		} else if(lazy[treeNode].val == 0){
			tree[treeNode].sos = (end-start+1) * lazy[treeNode].add * lazy[treeNode].add;
			tree[treeNode].sum = (end-start+1) * lazy[treeNode].add;
			if(start != end){
				lazy[2*treeNode].add = lazy[treeNode].add;
				lazy[2*treeNode+1].add = lazy[treeNode].add;
				lazy[2*treeNode].val = 0;
				lazy[2*treeNode+1].val = 0;
			}
		}
	}
	lazy[treeNode].add = 0;
	lazy[treeNode].val = 2;
}
void update1(tree1* tree,lazy1* lazy,ll left,ll right,ll start,ll end,ll treeNode,ll upd){
	lazytree(tree,lazy,start,end,treeNode);

	if(start > right || left > end)
		return;
	if(left <= start && right >= end){
		tree[treeNode].sos += (end-start+1) * upd * upd + 2*tree[treeNode].sum * upd;
		tree[treeNode].sum += (end-start+1) * upd;
		if(start != end){
			lazy[2*treeNode].add += upd;
			lazy[2*treeNode+1].add += upd;	
		}
		return;
	}
	ll mid = (start+end)/2;
	update1(tree,lazy,left,right,start,mid,2*treeNode,upd);
	update1(tree,lazy,left,right,mid+1,end,2*treeNode+1,upd);
	tree[treeNode].sum = tree[2*treeNode].sum + tree[2*treeNode+1].sum;
	tree[treeNode].sos = tree[2*treeNode].sos + tree[2*treeNode+1].sos;
}

void updatex(tree1* tree,lazy1* lazy,ll left,ll right,ll start,ll end,ll treeNode,ll upd){
	lazytree(tree,lazy,start,end,treeNode);

	if(start > right || left > end)
		return;
	if(left <= start && right >= end){
		tree[treeNode].sos = (end-start+1) * upd * upd;
		tree[treeNode].sum = (end-start+1) * upd;
		if(start != end){
			lazy[2*treeNode].add = upd;
			lazy[2*treeNode+1].add = upd;
			lazy[2*treeNode].val = 0; //set
			lazy[2*treeNode+1].val = 0;
		}
		return;
	}
	ll mid = (start+end)/2;
	updatex(tree,lazy,left,right,start,mid,2*treeNode,upd);
	updatex(tree,lazy,left,right,mid+1,end,2*treeNode+1,upd);
	tree[treeNode].sum = tree[2*treeNode].sum + tree[2*treeNode+1].sum;
	tree[treeNode].sos = tree[2*treeNode].sos + tree[2*treeNode+1].sos;
}

ll query(tree1* tree,lazy1* lazy,ll left,ll right,ll start,ll end,ll treeNode){
	lazytree(tree,lazy,start,end,treeNode);

	if(start > right || left > end)
		return 0;
	if(left <= start && right >= end){
		return tree[treeNode].sos;
	}
	ll mid = (start+end)/2;
	ll a = query(tree,lazy,left,right,start,mid,2*treeNode);
	ll b = query(tree,lazy,left,right,mid+1,end,2*treeNode+1);
	return a+b;
}
int main() {

	ll t;
	cin>>t;
	while(t--){
		ll n,q;
		cin>>n>>q;
		ll* arr = new ll[n];
		REP(i,0,n){
			cin>>arr[i];
		}
		lazy1* lazy = new lazy1[4*n];
		REP(i,0,4*n){
			lazy[i].val = 2;
			lazy[i].add = 0;
		}
		tree1* tree = new tree1[4*n];
		buildtree(tree,0,n-1,1,arr);
		REP(i,0,q){
			ll a;
			cin>>a;
			if(a==1){ //add
				ll st,ed,x;
				cin>>st>>ed>>x;
				update1(tree,lazy,st-1,ed-1,0,n-1,1,x);
			} else if(a==0){  //set
				ll st,ed,x;
				cin>>st>>ed>>x;
				updatex(tree,lazy,st-1,ed-1,0,n-1,1,x);
			} else {
				ll st,ed;
				cin>>st>>ed;
				cout<<query(tree,lazy,st-1,ed-1,0,n-1,1)<<endl;
			}
		}
	}
	return 0;
}