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
int mod = 1e9 + 7;
int main()
{
	i_os;
	ll m,n;
	cin>>n>>m;
	ll dp[11][1002];
	ll dp1[11][1002];
	REP(i,1,n+1){
		dp[0][i] = 1;
	}
	REP(i,1,m){
		REP(j,1,n+1){
			REP(k,1,j+1){
				dp[i][j] = (dp[i][j] + dp[i-1][k]) % mod;
			}
		}
	}
	REP(i,1,n+1){
		dp1[0][i] = 1;
	}
	REP(i,1,m){
		REP(j,1,n+1){
			REP(k,j,n+1){
				dp1[i][j] = (dp1[i][j] + dp1[i-1][k])% mod;
			}
		}
	}
	ll ans = 0;
	REP(i,1,n+1){
		REP(j,i,n+1){
			ans = (ans + (dp[m-1][i]*dp1[m-1][j]) % mod) % mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}