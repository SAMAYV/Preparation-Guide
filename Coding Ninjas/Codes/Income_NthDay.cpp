// fn = fn-1 + fn-2 + fn-1*fn-2
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int mod = 1e9 + 7;
ll matexp(ll a,ll b,ll c){
    if(b==0)
        return 1 % c;
    ll x = matexp(a,b/2,c);
    ll y = (x*x) % c;
    if(b%2!=0){
        y = (y*a) % c;
    }
    return y;
}
void multiply(ll M[2][2],ll A[2][2]){
    ll one = (M[0][0]*A[0][0] + M[0][1]*A[1][0]) % (mod-1);
    ll two = (M[0][0]*A[0][1] + M[0][1]*A[1][1])  % (mod-1);
    ll three = (M[1][0]*A[0][0] + M[1][1]*A[1][0])  % (mod-1);
    ll four = (M[1][0]*A[0][1] + M[1][1]*A[1][1])  % (mod-1);
    M[0][0] = one;
    M[0][1] = two;
    M[1][0] = three;
    M[1][1] = four;
}
void power(ll M[2][2],ll n){
    if(n==0 || n==1)
        return;
    power(M,n/2);
    multiply(M,M);
    if(n%2!=0){
        ll A[2][2] = {{1,1},{1,0}};
        multiply(M,A);
    }
}
ll fib(ll n){
    ll M[2][2] = {{1,1},{1,0}};
    power(M,n-1);
    return M[0][0];
}

ll income(ll f0,ll f1,ll n){
    ll x = fib(n-1);
    ll y = fib(n);
    // cout<<x<<" "<<y<<endl;
    ll z = (matexp(f0+1,x,mod)*matexp(f1+1,y,mod)) % mod;
    return z - 1;
}
int main() {

	int t;
    cin>>t;
    while(t--){
        ll f0,f1,n;
        cin>>f0>>f1>>n;
        if(n==0)
            cout<<f0<<endl;
        else if(n==1)
            cout<<f1<<endl;
        else
            cout<<income(f0,f1,n)<<endl;
    }
}