#include <bits/stdc++.h>
#define ll long long 
using namespace std;
int mod = 5*pow(10,6);
void update(int** BIT,int index,ll value,int row){
    for(int i=index;i<=100001;i+=(i&(-i))){
        BIT[row][i] = (BIT[row][i] + value) % mod;
    }
}
ll query(int** BIT,int index,int row){
    ll count = 0;
    for(int i=index;i>0;i-=(i&(-i))){
        count = (count + BIT[row][i]) % mod;
    }
    return count;
}
int main()
{
    int n,k;
    cin>>n>>k;
    int** BIT = new int*[k+1];
    for(int i=0;i<k+1;i++)
        BIT[i] = new int[100002]();
    
    int* a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    
    update(BIT,a[0]+1,1,1);
    
    int max = a[0];
    for(int c=1;c<n;c++){
        
        if(a[c]>max)
            max = a[c];
        
        update(BIT,a[c]+1,1,1);
        
        for(int r=2;r<=k;r++){
            ll q = query(BIT,a[c],r-1);
            update(BIT,a[c]+1,q,r);
        }
        
    }
    cout<<query(BIT,max+1,k)<<" ";
    return 0;
}
