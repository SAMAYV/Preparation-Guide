#include<bits/stdc++.h>
using namespace std;
#define ll long long
void phifunction(ll* phi){
    for(int i=0;i<=1000000;i++)
        phi[i] = i;
    for(int i=2;i<=1000000;i++){
        if(phi[i]==i){
            phi[i] = i-1;
            for(int j=2;j<=1000000/i;j++)
                phi[i*j] = (phi[i*j]*(i-1))/i;
        }
    }
}
void divisor(ll* arr,ll* phi){
    for(int i=1;i<=1000000;i++){
        for(int j=2;j<=1000000/i;j++){
            arr[i*j] += i*phi[j];
        }
    }
}
ll* gcdd(){
    ll* phi = new ll[1000001];
    phifunction(phi);
    ll* gcd = new ll[1000001]();
    gcd[2] = 1;
    ll* arr = new ll[1000001]();
    divisor(arr,phi);
    for(int i=3;i<=1000000;i++){
        gcd[i] = gcd[i-1] + arr[i];
    }
    return gcd;
}
int main() {
    int t;
    cin>>t;
    ll* gcd = gcdd();
    while(t!=0){
        cout<<gcd[t]<<endl;
        cin>>t;
    }
    return 0;
}