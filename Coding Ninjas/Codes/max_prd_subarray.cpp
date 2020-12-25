#include <bits/stdc++.h>
using namespace std;
int maxprd(int* a,int n){
	int** dp = new int*[2];
	for(int i=0;i<2;i++)
		dp[i] = new int[2]();
	int max = a[0];
	dp[0][0] = a[0];
	dp[1][0] = a[0];
	for(int i=1;i<n;i++){
		if(a[i]>0){
			dp[0][1] = a[i] > a[i]*dp[0][0] ? a[i] : a[i]*dp[0][0];
			dp[1][1] = a[i]*dp[1][0] < a[i] ? a[i]*dp[1][0] : a[i];
		}
		else if(a[i]<0){
			dp[0][1] = a[i] > a[i]*dp[1][0] ? a[i] : a[i]*dp[1][0];
			dp[1][1] = a[i]*dp[0][0] < a[i] ? a[i]*dp[0][0] : a[i];	
		}
		max = max > dp[0][1] ? max : dp[0][1];
		dp[0][0] = dp[0][1];
		dp[1][0] = dp[1][1];
		dp[0][1] = 0;   dp[1][1] = 0;
	}
	return max;
}
int main()
{
	int n;
	cin>>n;
	int* a = new int[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<maxprd(a,n);
	return 0;
}