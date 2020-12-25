#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a,ll b){
    if(b==0)
        return a;
    return gcd(b, a % b);
}
void lcm(ll n){
	ll sum = 2*n;
	for(int i=2;i<n;i++){
		ll g = gcd(n,i);
        sum = sum + i*(n/g);
	}
	cout<<sum;
}
void lcm2(ll n){
    ll* a = new ll[n+1];
    for(ll i=0;i<n+1;i++)
        a[i] = i;
    
    for(ll i=2;i<=n;i++){
        if(a[i]==i){
            a[i] = i-1;
            for(ll j=2;j<=n/i;j++){
                a[j*i] = (a[j*i]*(i-1))/i; 
            }
        }
    }
    
    ll sum = 1;
    for(ll i=1;i<=sqrt(n);i++){
        if(n % i == 0){
            // i is a divisor
            if(i*i == n)
                sum += a[i]*i;
            else
                sum += a[i]*i + (a[n/i]*n)/i;
        }
    }
    sum = (sum*n)/2;
    cout<<sum;
}
void func(long long n)
{
	// lcm(n);
    lcm2(n);
}
