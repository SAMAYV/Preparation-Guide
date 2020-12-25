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
ll matrix(int** arr,int n,int m){
	ll ct = 0;
	for(int c=0;c<m;c++){
		ll min = INT_MAX;
		unordered_map<int,ll> um;
		REP(r,0,n){
			if(arr[r][c]%m != c || (n-1)*m + c < arr[r][c])
				continue;
			int pos = arr[r][c]/m;
			int shift = (r-pos+n)%n;
			um[shift]++;
		}
		REP(r,0,n){
			if(n-um[r]+r < min)
				min = n-um[r]+r;
		}
		ct += min;
	}
	return ct;
}
int main()
{
	int n,m;
	cin>>n>>m;
	int** arr = new int*[n];
	REP(i,0,n){
		arr[i] = new int[m];
		REP(j,0,m){
			cin>>arr[i][j];
			arr[i][j] -= 1;
		}
	}
	cout<<matrix(arr,n,m)<<endl;
	return 0;
}