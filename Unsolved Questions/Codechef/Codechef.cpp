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
ll xorf(ll n){
	if(n == -1){
		return 0;
	} else if(n % 4 == 1){
		return 1;
	} else if(n % 4 == 2){
		return n+1;
	} else if(n % 4 == 3){
		return 0;
	} else {
		return n;
	}
}
bool compare1(pair<ll,ll> p1,pair<ll,ll> p2){
	return p1.second < p2.second;
}
bool compare2(pair<ll,ll> p1,pair<ll,ll> p2){
	return p1.first < p2.first; 
}
int main()
{
	ll n,q;
	cin>>n>>q;
	set<pair<ll,ll>> s;
	s.insert({1,n});
	REP(i,0,q){
		ll a,b;
		cin>>a>>b;
		if(a == 1){
			auto t = s.lower_bound({-1,b},compare1);
			pair<ll,ll> p = *t;
			if(p.first <= b && p.second >= b){
				s.erase(p);
				if(p.first <= b-1)
					s.insert({p.first,b-1});
				if(b+1 <= p.second)
					s.insert({b+1,p.second});
			}
		}
		else {
			auto t = s.lower_bound({b,-1},compare2);
			pair<ll,ll> p = *t;
			cout<<xorf(p.second) - xorf(p.first-1)<<endl;
		}
	}
	return 0;
}