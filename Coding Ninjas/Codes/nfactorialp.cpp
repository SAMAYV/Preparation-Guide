#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll modexp(ll a,ll b,ll c){
    if(b==0)
        return 1;
    ll small = modexp(a,b/2,c);
    ll small1 = (small*small) % c;
    if(b%2!=0)
        small1 = (small1 * a) % c;
    return small1;
}
ll nfactorialp(ll n,ll p){
    ll prd = 1;
    for(ll i=n+1;i<p;i++){
        prd = (prd * modexp(i,p-2,p)) % p;
    }
    return p - prd;
}
int main() {

	int t;
    cin>>t;
    while(t--){
        ll n,p;
        cin>>n>>p;
        if(n>=p)
            cout<<0<<endl;
        else
            cout<<nfactorialp(n,p)<<endl;
    }
}