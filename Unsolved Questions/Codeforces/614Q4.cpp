#include <bits/stdc++.h>
using namespace std;
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
ll min(ll a,ll b){
	return a < b ? a : b;
}
int main()
{
	i_os;
	ll x0, y0, ax, ay, bx, by;
	ll xs, ys, t;
	cin>>x0>>y0>>ax>>ay>>bx>>by;
	cin>>xs>>ys>>t;
	vector<pair<ll,ll>> v;
	ll x = x0, y = y0;
	while((x-xs + y-ys) <= t){
		if(abs(x-xs) + abs(y-ys) > t){
			x = ax*x + bx;
			y = ay*y + by;
			continue;
		}
		else 
			v.push_back(make_pair(x,y));
		x = ax*x + bx;
		y = ay*y + by;
	}
	// while(x < 2*1e16 && y < 2*1e16){
	// 	v.push_back(make_pair(x,y));
	// 	x = ax*x + bx;
	// 	y = ay*y + by;
	// }
	// cout<<v.size()<<endl;
	ll m = 0;
	// ll m1,m2,m3 = INT_MAX;
	// ll tl = 0;
	for(ll i=0;i<v.size();i++){
		// if(abs(v[i].first-xs) + abs(v[i].second-ys) > t)
		// 	continue;
		for(ll j=i;j<v.size();j++){
			ll nodes_covered = 0;
			ll time_left;
			for(ll k=j;k<v.size();k++)
			{
				time_left = t - abs(xs-v[j].first) - abs(ys-v[j].second);
				nodes_covered = 1;
				if(abs(v[k].first-v[i].first) + abs(v[k].second-v[i].second) > time_left)
					continue;
				time_left = time_left - (abs(v[k].first-v[i].first) + abs(v[k].second-v[i].second));
				ll y = min(abs(v[k].first-v[j].first) + abs(v[k].second-v[j].second), abs(v[i].first-v[j].first) + abs(v[i].second-v[j].second));
				if(y > time_left)
					continue; 
				nodes_covered += k - i;
				if(nodes_covered > m){
					m = nodes_covered;
					// m1 = i; m2 = j; m3 = k;
					// tl = time_left;
				}
			}
		}
	}
	cout<<m<<endl;
	// cout<<m1<<" "<<m2<<" "<<m3<<" "<<tl<<endl;
	return 0;
}