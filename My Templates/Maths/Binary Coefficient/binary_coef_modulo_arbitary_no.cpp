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

ll multiplicity_factorial(ll n,ll p){
    ll count = 0;
    do {
        n /= p;
        count += n;
    } while (n);
    return count;
}

// when mod is power of some prime number and n is of the order <= 1e6
ll C(ll n,ll k,vector<ll>& fact,vector<ll>& ifact,int mod)
{
	// let the mod = p^b
	if(p > max(k,n-k)){
		// use the usual technique
		ll ans = fact[n];
		ll gn = multiplicity_factorial(n,p);
		ans *= power(p,gn,mod);
		ans %= mod;
		ans *= ifact[n-k];
		ans %= mod;
		ans *= ifact[k];
		ans %= mod;
		return ans;
	}
	else {
		ll gn = multiplicity_factorial(n,p);
		ll gk = multiplicity_factorial(k,p);
		ll gnk = multiplicity_factorial(n-k,p);
		if(gn - gk - gnk >= b){
			return 0;
		}
		else {
			ll ans = fact[n];
			ans *= ifact[n-k];
			ans %= mod;
			ans *= ifact[k];
			ans %= mod;
			ans *= power(p,gn-gk-gnk,mod);
			ans %= mod;
			return ans;
		}
	}
}

void preprocess(ll N,vector<ll>& fact,vector<ll>& ifact,int mod){
	// mod is of form p^b
	fact.resize(N,1);
	ifact.resize(N,1);
	REP(i,1,N){
		ll pt = i;
		while(pt % p == 0){
			pt /= p;
		}
		fact[i] = fact[i-1]*pt;
		fact[i] %= mod;
	}
	REP(i,1,N){
		ll pt = i;
		while(pt % p == 0){
			pt /= p;
		}
		ifact[i] = ifact[i-1]*power(pt,mod-2,mod);
		ifact[i] %= mod;
	}
}

ll calc(ll n,ll k,vector<ll>& a,vector<ll>* fact,vector<ll>* ifact,ll mod1){
	// chinese remainder theroem
	vector<ll> arr;
	REP(i,0,a.size()){
		arr.push_back(C(n,k,fact[i],ifact[i],a[i]));
	}
	ll ans = 0;
	REP(i,0,arr.size()){
		ll p = arr[i] % mod1;
		p *= (mod1/a[i]);
		p %= mod1;
		p *= power(mod1/a[i],a[i]-2,a[i]);
		p %= mod1;
		ans += p;
		ans %= mod1;
	}
	return ans;
}

void binary_coef_modulo_arbitary_no(ll mod){
	// prime factorise mod
	vector<ll> a;
	vector<ll> fact[20],ifact[20];
	ll ct = 0, mod1 = mod;
	REP(i,2,sqrt(mod1) + 1){
		ll p = 0;
		while(mod % i == 0){
			mod /= i;
			p++;
		}
		if(p > 0){
			preprocess(100000LL,fact[ct],ifact[ct],powl(i,p));
			a.push_back(powl(i,p));
			ct++;
		}
	}
	if(mod > 1){
		preprocess(100000LL,fact[ct],ifact[ct],mod);
		a.push_back(mod);
		ct++;
	}
	// calc for n,k
	ll n,k;
	cin>>n>>k;
	cout<<calc(n,k,a,fact,ifact,mod1)<<endl; 
}
int main()
{
		
	return 0;
}