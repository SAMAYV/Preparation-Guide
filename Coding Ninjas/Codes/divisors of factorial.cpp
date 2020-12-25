#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
int mod = pow(10,9) + 7;
void sieve(int n,bool* arr){
    arr[0] = false;
    arr[1] = false;
    for(int i=2;i<=n;i++){
        if(arr[i]){
            for(int j=2;j<=n/i;j++)
                arr[j*i] = false;
        }
    }
}
void divisors(int n){
    bool* arr = new bool[n+1];
    for(int i=0;i<=n;i++)
        arr[i] = true;
    sieve(n,arr);
    ll p = 1;
    for(int i=2;i<=n;i++){
        ll sum = 0;
        if(arr[i])
        {
            int k = 1;
            ll val = pow(i,k);
            while(val <= n){
                sum = sum + n/val;
                k += 1;
                val = pow(i,k);
            }
            p = (p * (sum + 1)) % mod;
        }
    }
    cout<<p<<endl;
}
int main(){
	int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        divisors(n);
    }
	return 0;
}