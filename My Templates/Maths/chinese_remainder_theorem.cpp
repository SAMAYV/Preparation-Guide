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

class Extended {
	public:
	ll x,y,gcd;
};
Extended ExtendedEuclid(ll a,ll b){
	if(b == 0){
		Extended e;
		e.x = 1;
		e.y = 0;
		e.gcd = a;
		return e;
	}
	Extended small = ExtendedEuclid(b,a % b);
	Extended ans;
	ans.x = small.y;
	ans.y = small.x - (a/b)*small.y;
	ans.gcd = small.gcd;
	return ans;
}
ll mmInverse(ll a,ll m){
	Extended e = ExtendedEuclid(a,m);
	return (e.x + m) % m;
}
ll chinese_remainder(vector<ll>& a,vector<ll>& m,ll n){
	ll prd = 1;
	REP(i,0,n){
		prd *= m[i];
	}
	ll ans = 0;
	REP(i,0,n){
		ll Xi = prd / m[i];
		ll Xi_inv_mod_mi = mmInverse(Xi,m[i]);
		ans += a[i] * Xi * Xi_inv_mod_mi;
	}
	return ans;
}
int main() 
{ 
	ll n;
	cin>>n;
	ll a[n],m[n];
	// solves x = a1modm1; x = a2modm2; .... x = anmodmn with each pair of m being coprime
	return 0;	 
} 