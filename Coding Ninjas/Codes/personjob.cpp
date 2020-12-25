#include<bits/stdc++.h>
using namespace std;
int DP(int job[4][4],int n){
	int* dp = new int[1<<n];
	for(int i=0;i<(1<<n);i++)
		dp[i] = INT_MAX;

	dp[(1<<n) - 1] = 0;
	for(int i=(1<<n)-2; i>=0; i--){
		int min = INT_MAX;
		int count = 0;
		for(int j=0;j<n;j++){
			if((1<<j)&i)
				count++;
		}
		// cout<<count<<" ";
		for(int j=0;j<n;j++){
			if(!((1<<j)&i)){
				if(job[count][j] + dp[i|(1<<j)] < min)
					min = job[count][j] + dp[i|(1<<j)];
			}
		}
		dp[i] = min;
	}
	// for(int i=0;i<(1<<n);i++)
	// 	cout<<dp[i]<<" ";
	return dp[0];
}
int main()
{
	int job[4][4] = {{10,2,6,5},{1,15,12,8},{7,8,9,3},{15,13,4,10}};
	cout<<DP(job,4);
}