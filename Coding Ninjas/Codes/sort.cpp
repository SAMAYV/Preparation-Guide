#include<bits/stdc++.h>
#include<ctime>
using namespace std;
#define REP(i,f,n) for(int i=0;i<n;i+=f)
int main()
{
	int n;
	cin>>n;
	int* a = new int[n];
	REP(i,1,n){
		cin>>a[i];
	}
	int s = -1, e = -1;
	int max = -1e9;
	int start = clock();
	REP(i,1,n){
		if(i+1 < n && a[i]>a[i+1]){
			if(s==-1)
				s = i;
			e = i+1;
			if(a[i]>max)
				max = a[i];
		}
		else {
			if(a[i]<max)
				e = i;
		}
	}
	int end = clock();
	double diff = (double)(start-end)/CLOCKS_PER_SEC;
	cout<<s<<" "<<e<<" "<<diff<<endl;
	return 0;
}