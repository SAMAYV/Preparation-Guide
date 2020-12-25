#include <bits/stdc++.h>
using namespace std;
int rectangle(int** a,int m,int n){
	int** sum = new int*[m];
	for(int i=0;i<m;i++)
		sum[i] = new int[n];
	
	sum[m-1][n-1] = a[m-1][n-1];
	for(int r=m-2;r>=0;r--)
		sum[r][n-1] = sum[r+1][n-1] + a[r][n-1];
	for(int c=n-2;c>=0;c--)
		sum[m-1][c] = sum[m-1][c+1] + a[m-1][c];

	for(int i=m-2;i>=0;i--)
		for(int j=n-2;j>=0;j--){
			sum[i][j] = sum[i+1][j] + sum[i][j+1] - sum[i-1][j-1] + a[i][j];
		}

	int max = INT_MIN;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			for(int k=i;k<m;k++){
				for(int l=j;l<n;l++){
					//i  and j are starting points
					//k and l are ending points
					if(sum[i][j] - sum[k+1][j] - sum[i][l+1] + sum[k+1][l+1] > max)
						max = sum[i][j] - sum[k+1][j] - sum[i][l+1] + sum[k+1][l+1]; 
				}
			}
		}
	}
	return max;
}
int main()
{
	int m,n;
	cin>>m>>n;
	int** a = new int*[m];
	for(int i=0;i<m;i++)
		a[i] = new int[n];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];

	cout<<rectangle(a,m,n);
	return 0;
}