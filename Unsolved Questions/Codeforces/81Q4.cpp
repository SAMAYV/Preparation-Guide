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
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
ll gcd(ll x,ll y)
{
    if(x==0) return y;
    return gcd(y%x,x);
}
vector<ll>* prime(ll n){
	ll k = n;
	vector<ll>* v = new vector<ll>();
	REP(i,2,sqrt(n)+1){
		ll val = 0;
		while(n % i == 0){
			val = i;
			n /= i;
		}
		if(val!=0)
			v->push_back(val);
		if(n==1)
			break;
	}
	if(n != 1 && n != k)
		v->push_back(n);
	// cout<<v->size()<<endl;
	return v;
}
ll max(ll a,ll b){
	return a > b ? a : b;
}
ll min(ll a,ll b){
	return a < b ? a : b;
}
int main()
{
	int t;
	cin>>t;
	while(t--){
		ll a,m;
		cin>>a>>m;
		ll m1 = m/gcd(max(m,a),min(m,a));
		// cout<<m1<<" ";
		ll phi = m1;
		vector<ll>* v = prime(m1);
		if(v->size()==0){
			cout<<phi-1<<endl;
			continue;
		}
		REP(i,0,v->size()){
			phi = (phi*(v->at(i)-1))/v->at(i);
		}
		cout<<phi<<endl;
	}
	return 0;
}