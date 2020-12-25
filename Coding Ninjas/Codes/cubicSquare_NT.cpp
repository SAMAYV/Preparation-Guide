/*Varun is learning method of successive squaring so that he can calculate a^b mod m quickly. To give himself practice he wrote many tuples of a, b and m and went to school thinking that he will do it after school.
After school he found that tuples he wrote are modified by his little sister. His sister converted each b into base 3. Varun wrote everything in base 10.
Help Varun to do his excercise.*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll cubic(ll a,string b,ll m){
    ll p = 1;
    ll y = a;
    for(int i=b.size()-1;i>=0;i--){
        if(b[i] - '0'==1){
            p = (p%m * y%m) %m;    
        }
        else if(b[i] - '0'==2){
            p = ((p%m * y%m) %m * y%m) %m;    
        }
        y = ((y%m * y%m) %m * y%m) %m;
    }
    return p;
}
int main() {
    int t;
    cin>>t;
    while(t--){
        ll a,m;
        string b;
        cin>>a>>b>>m;
        cout<<cubic(a,b,m)<<endl;
    }
}