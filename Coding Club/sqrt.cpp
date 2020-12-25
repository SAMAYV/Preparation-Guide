#include <bits/stdc++.h>
using namespace std;
#define REP(i,f,n) for(int i=0;i<n;i+=f)
#define ll long long
int main()
{
	int n;
	cin>>n;
	float l = 0;
	float u = n;
	float mid;
	int p;
	cin>>p;
	while(u - l > pow(10,-p-1)){
		mid = (l+u)/2;
		if(mid*mid == n){
			cout<<mid<<endl;
			return 0;
		}
		else if(mid*mid > n){
			u = mid;
		}
		else {
			l = mid;
		}
	}
	cout<<fixed<<setprecision(p)<<mid<<endl;
}