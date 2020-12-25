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
ll min(ll a,ll b){
	return a < b ? a : b;
}
ll Evil(ll* arr,ll n,ll index){
	if(index==-1)
		return 0;

	ll a[n]; ll b[n];
	ll s1 = 0,s2 = 0;
	REP(i,0,n){
		if((arr[i]>>index) & 1){
			a[s1] = arr[i];
			s1++;
		}
		else {
			b[s2] = arr[i];
			s2++;
		}
	}
	if(s1==n || s2==n){
		return Evil(arr,n,index-1);
	}
	else {
		ll ans1 = Evil(a,s1,index-1);
		ll ans2 = Evil(b,s2,index-1);
		return (1<<index) + min(ans1,ans2);
	}
}
int main()
{
	ll n;
	cin>>n;
	ll* arr = new ll[n];
	REP(i,0,n){
		cin>>arr[i];
	}
	cout<<Evil(arr,n,31);
	return 0;
}