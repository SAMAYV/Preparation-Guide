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

void pre_compute(ll n,vector<vector<ll>>& arr,ll succ[]){
	arr.resize(20,vector<ll>(n));
	REP(j,1,n+1){
		arr[0][j] = succ[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = arr[i - 1][j];
			arr[i][j] = arr[i - 1][p];
		}
	}
}
ll kth_successor(ll x,ll k,vector<vector<ll>>& arr){
	ll p = x;
	REP(i,0,60){
		if((k >> i) & 1){
			p = arr[i][p];
		}
	}
	return p;
}
int main() 
{ 
	ll n;
	cin>>n;
	// each edge is from (x to succ(x))
	ll succ[n+1];
	REP(i,1,n+1){
		cin>>succ[i];
	}
	vector<vector<ll>> arr;
	pre_compute(n,arr,succ);
	
	ll q;
	cin>>q;
	while(q--){
		ll x,k;
		cin>>x>>k;
		cout<<kth_successor(x,k,arr)<<endl;
	}
	return 0;	
} 
