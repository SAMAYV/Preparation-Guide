#include <bits/stdc++.h>
using namespace std;
int DP(int* a,int n,int k){
	int** dp = new int*[k];
	for(int i=0;i<k;i++){
		dp[i] = new int[n]();
	}
	int x = a[0] % k;
	dp[x][0] = 1;

	for(int c=1;c<n;c++){
		int l = a[c] % k;
			dp[l][c]++;
		for(int r=0;r<k;r++){
			int x = (a[c] + r) % k;
			dp[x][c] += dp[r][c-1];
			dp[r][c] += dp[r][c-1];
		}
	}
	// for(int r=0;r<k;r++){
	// 	for(int c=0;c<n;c++)
	// 		cout<<dp[r][c]<<" ";
	// 	cout<<endl;
	// }
	return dp[0][n-1];
}
int main()
{
	int n,k;
	cin>>n>>k;
	int* a = new int[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<DP(a,n,k);
}