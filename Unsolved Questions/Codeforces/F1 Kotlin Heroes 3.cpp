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

int main()
{
	ll n,m;
	cin>>n>>m;
	ll* arr = new ll[n];
	ll ind = -1;
	REP(i,0,n){
		cin>>arr[i];
		if(arr[i] == m)
			ind = i;
	}
	vector<ll> v1(ind),v2(n-ind-1);	
	REP(i,0,ind){
		v1[ind-i-1] = arr[i];
	}
	REP(i,ind+1,n){
		v2[i-ind-1] = arr[i];
	}
	ll dp1[v1.size()],dp2[v2.size()];
	
	unordered_map<ll,ll> umL,umR;
	//store big - small
	ll diff = 0;
	umL[0] = 1;  umR[0] = 1;
	REP(i,0,v1.size()){
		// cout<<v1[i]<<" ";
		if(v1[i] < m) diff--;
		else diff++;
		umL[diff]++;
	}
	// cout<<endl;
	diff = 0;
	REP(i,0,v2.size()){
		if(v2[i] < m) diff--;
		else diff++;
		umR[diff]++;	
	}
	ll ans = 0;
	REP(i,-n,n+1){
		ll l = i;
		ll r1 = -i, r2 = -i+1;
		if(umL.count(l) && umR.count(r1)){
			ans += umL[l]*umR[r1];
		}
		if(umL.count(l) && umR.count(r2)){
			ans += umL[l]*umR[r2];
		}
	}
	cout<<ans<<endl;
	return 0;
}