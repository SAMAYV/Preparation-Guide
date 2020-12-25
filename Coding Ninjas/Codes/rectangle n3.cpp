#include <bits/stdc++.h>
using namespace std;
int f(int* sum,int m){
	int s = 0;
	int* v = new int[m];
	for(int i=0;i<m;i++){
		if(v[i-1]<=0)
			v[i] = sum[i];
		else {
			v[i] = v[i-1] + sum[i];
		}

		if(v[i]>max)
			max = v[i];
	}
	return s;
}
int rectangle(int** a,int m,int n){
	int max = INT_MIN;
	for(int i=0;i<n;i++){

		int* sum = new int[m];
		for(int i=0;i<m;i++)
			sum[i] = 0;

		for(int j=i;j<n;j++){
			for(int k=0;k<m;k++){
				sum[k] += a[k][j];
			}
			int x = f(sum,m);
			if(max < x)
				max = x;
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
		for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    
    cout<<rectangle(a,m,n);
	return 0;
}