#include <bits/stdc++.h>
using namespace std;
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
ll max(ll a,ll b){
	return a > b ? a : b;
}
ll min(ll a,ll b){
	return a < b ? a : b;
}
struct path {
	ll x,y;
};
bool compare(path p1,path p2){
	if(p1.x==p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}
int main()
{
	i_os;
	ll q,x;
	cin>>q>>x;
	ll curr_mex = 0;
	// set<ll> s;
	ll query;
	// ll max = INT_MIN;
	unordered_map<ll,ll> um;
	REP(i,0,q){
		cin>>query;
		// if(query > max)
		// 	max = query;
		ll var = query % x;
		um[var]++;
		// s.insert(var);
		REP(j,curr_mex,i+2){
			ll curmex = curr_mex % x;
			if(um.count(curmex)!=0 && um[curmex]>0){
				um[curmex]--;
				curr_mex++;
			}
			else {
				break;
			}
		}
		cout<<curr_mex<<endl;
	}
	return 0;
}