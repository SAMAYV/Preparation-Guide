#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll noofdigits(ll b){
	if(b < 10)
		return 0;

	return 1 + noofdigits(b/10);
}
ll powM(ll x,ll y)
{
    if(y==0) return 1;
    ll p = powM(x,y/2);
    p=(p*p);
    return (y%2==0) ? p : (x*p);
}
int main()
{
	int t;
	cin>>t;
	while(t--){
		ll n,d;
		cin>>n>>d;
		if(d<=n)
			cout<<"YES"<<endl;
		// else if(n >= (1+ d/2))
		// {
		// 	ll k = sqrt(d);
		// 	// if(k*k== d){
		// 		if(n+1 <= 2*k)
		// 			cout<<"YES"<<endl;
		// 		else
		// 			cout<<"NO"<<endl;
		// 	// }
		// 	// else {
		// 	// 	if(n+1 <= 2*(k+1))
		// 	// 		cout<<"YES"<<endl;
		// 	// 	else
		// 	// 		cout<<"NO"<<endl;
		// 	// }
		// }
		else {
			int st = 0;
			int ed = n-1;
			int mid;
			int flag = 0;
			while(st <= ed){
				mid = (st+ed)/2;
				if(mid + d/(mid+1) <=n && d % (mid+1)==0){
					cout<<"YES"<<endl;
					flag = 1;
					break;
				}
				else if(mid + d/(mid+1) + 1 <=n && d % (mid+1)!=0){
					cout<<"YES"<<endl;
					flag = 1;
					break;					
				}
				else {
					st = mid + 1;
				}
			}
			if(flag == 0)
			cout<<"NO"<<endl;
		}
	}
	return 0;
}