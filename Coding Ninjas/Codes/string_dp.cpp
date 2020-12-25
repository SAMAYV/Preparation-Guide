#include<bits/stdc++.h>
using namespace std;
#define ll long long
int mod = 1e9 + 7;
int DP(string s){
	int n = s.length();
	
	ll* power = new ll[n+1];
	power[0] = 1;
	for(int i=1;i<n+1;i++)
		power[i] = (power[i-1]*26) % mod;

	ll** dp = new ll*[n+1];
	for(int i=0;i<=n;i++)
		dp[i] = new ll[n+1]();

	for(int c=1;c<=n;c++){
		for(int r=n;r>0;r--){
			if(r > c)
				continue;
			if(r==c){
				dp[r][c] = 'Z' - s[r-1];
				continue;
			}
			ll val = (((power[c-r-1]*('Z'-s[r-1])) % mod)*('Z'-s[c-1])) % mod;
			dp[r][c] = (((val + dp[r+1][c]) % mod + dp[r][c-1]) % mod - dp[r+1][c-1] + mod) % mod;
		}
	}
	for(int r=1;r<=n;r++){
		for(int c=1;c<=n;c++)
			cout<<dp[r][c]<<" ";
		cout<<endl;
	}
	return dp[1][n];
}
int main()
{
	string s;
	cin>>s;
	cout<<DP(s);
}