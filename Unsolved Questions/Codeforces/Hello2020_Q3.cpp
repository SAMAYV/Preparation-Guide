#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int n,m;
	cin>>n>>m;
	ll* fact = new ll[n+1];
	fact[0] = 1;
	for(ll i=1;i<n+1;i++)
		fact[i] = (fact[i-1]*(i % m)) % m;
	ll count = 0;
	for(int i=0;i<n;i++){
		count = (count + (((((n-i) % m)*fact[i+1]) % m)*fact[n-i]) % m) % m;
	}
	cout<<count<<endl;
	return 0;
}