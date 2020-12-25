#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
int dp[101][101][101][2];
int DP(int* a,int pos,int even,int odd,int last){
	if(even < 0 || odd < 0)
		return INT_MAX;
	if(pos==n)
		return 0;
	if(dp[pos][even][odd][last]!=INT_MAX)
		return dp[pos][even][odd][last];
	if(a[pos]!=-1){
		ll k = DP(a,pos+1,even,odd,a[pos]) + (last!=a[pos]);
		dp[pos][even][odd][last] = k;
	}
	else {
		ll k = INT_MAX;
		ll l = INT_MAX;
		if(even > 0){
			k = DP(a,pos+1,even-1,odd,0) + (last==1);
		}
		if(odd > 0){
			l = DP(a,pos+1,even,odd-1,1) + (last==0);
		}
		dp[pos][even][odd][last] = min(k,l);	
	}
	return dp[pos][even][odd][last];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	int* a = new int[n];
	int ev = 0;  int od = 0;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]==0)
			a[i] = -1;
		else if(a[i]%2==0){
			a[i] = 0;
			ev++;
		}
		else{
			a[i] = 1;
			od++;
		}
	}
	for(int i=0;i<101;i++){
		for(int j=0;j<101;j++){
			for(int k=0;k<101;k++){
				dp[i][j][k][0] = INT_MAX;
				dp[i][j][k][1] = INT_MAX;
			}
		}
	}
	ev = n/2 - ev;
	od = (n+1)/2 - od;
	if(a[0]!=-1)
		cout<<DP(a,1,ev,od,a[0]);
	else {
		cout<<min(DP(a,1,ev-1,od,0),DP(a,1,ev,od-1,1));
	}
	return 0;
}