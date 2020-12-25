/* find max of j-i if a[i]<=a[j]*/
#include <bits/stdc++.h>
using namespace std;
#define REP(i,f,n) for(int i=0;i<n;i+=f)
int main()
{
	int n;
	cin>>n;
	pair<int,int> a[n];
	REP(i,1,n){
		cin>>a[i].first;
		a[i].second = i;
	}
	sort(a,a+n);
	int maxv = -1e9;
	int maxi = a[n-1].second;
	for(int i=n-2;i>=0;i--){
		if(maxi - a[i].second > maxv)
			maxv = maxi - a[i].second;
		maxi = max(maxi,a[i].second);
	}
	cout<<maxv;
	return 0;
}