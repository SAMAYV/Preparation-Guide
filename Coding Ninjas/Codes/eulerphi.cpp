// Sehwag has been solving a lot of mathematical problems recently. 
// He was learning ETF (Euler Totient Function) and found the topic quite interesting. So, he tried solving a question on ETF. 
// He will be given two numbers L and R. 
// He has to find the probability that the ETF of a number in the range [L, R] is divisible by a number K
#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<int>* sieve(){
    vector<int>* v = new vector<int>;
    bool* s = new bool[1000001];
    for(int i=0;i<1000001;i++)
        s[i] = true;
    s[0] = false;  s[1] = false;
    for(int i=2;i<1001;i++){
        if(s[i]){
            for(int j=i;j<=1000000/i;j++){
                s[i*j] = false;
            }
        }
    }
    for(int i=2;i<=1000001;i++){
        if(s[i])
            v->push_back(i);
    }
    return v;
}
void sehwag(ll left,ll right,ll k,vector<int>* v){
    ll* arr = new ll[right-left+1];
    ll* support = new ll[right-left+1];
    for(int i=0;i<right-left+1;i++){
        support[i] = i+left;
        arr[i] = i+left;
    } 
    int i=0;
    while(i < v->size() && v->at(i) <= right){
        int prime = v->at(i);
        ll base = (left/prime)*prime;
        if(base < left){
            base += prime;
        }
        for(int j=base;j<=right;j+=prime){
            arr[j-left] = (arr[j-left]*(prime-1))/prime;
            while(support[j-left] % prime ==0)
                support[j-left] /= prime;
        }
        i++;
    }
    float count = 0;
    for(int i=0;i<right-left+1;i++){
        if(support[i]!=1){
            arr[i] = (arr[i]*(support[i]-1))/support[i];
        }
        if(arr[i] % k ==0)
            count++;
        // cout<<arr[i]<<" ";
    }
    // cout<<count<<endl;
    float f = count/(right-left+1);
    cout<<fixed<<setprecision(6)<<f<<endl;
}
int main() {

	int t;
    cin>>t;
    vector<int>* v = sieve();
    while(t--){
        ll left,right,k;
        cin>>left>>right>>k;
        sehwag(left,right,k,v);
    }
}