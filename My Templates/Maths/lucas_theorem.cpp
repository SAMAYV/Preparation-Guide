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

ll power(ll x,ll y,ll m){
	if(y == 0)
		return 1;
	ll p = power(x, y/2, m);
	p = (p * p) % m;
    if(y % 2) p = (p * x) % m;
	return p;
}

// when mod is prime and n is of the order > 1e6 and mod <= 1e6
ll C(ll n,ll k,vector<ll>& fact,vector<ll>& ifact,int mod)
{
	if(k > n) return 0;  
	if(n < mod){
		ll res = fact[n];
		res = (res * ifact[k]) % mod;
		res = (res * ifact[n - k]) % mod;
		return res;
	}
	vector<ll> N, K;
	while(n){
		N.push_back(n % mod);
		n /= mod;
	}
	while(k){
		K.push_back(k % mod);
		k /= mod;       
	}
	ll res = 1;
	REP(i,0,K.size()){
		res = (res * C(N[i], K[i])) % mod;
	}
	return res;
}

void preprocess(ll N,vector<ll>& fact,vector<ll>& ifact,int mod){
	// mod is of form p^b
	fact.resize(N,1);
	ifact.resize(N,1);
	REP(i,1,N){
		fact[i] = fact[i-1]*i;
		fact[i] %= mod;
	}
	REP(i,1,N){
		ifact[i] = ifact[i-1]*power(i,mod-2,mod);
		ifact[i] %= mod;
	}
}

ll binary_coef_modulo_prime_no_for_big_n(int mod){
	vector<ll> fact,ifact;
	preprocess(100000LL,fact,ifact,mod);

	// answer queries for calculating nCk % mod for large n
	ll n,k;
	cin>>n>>k;
	cout<<C(n,k,fact,ifact,mod)<<endl;
}