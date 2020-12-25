#include<bits/stdc++.h>
using namespace std;
int mod = pow(10,9) + 7;
void update(int index,int value,int** BIT,int row){
    for(int i=index;i<=100000;i+=(i&(-i))){
        BIT[row][i] = (BIT[row][i] + value) % mod;
    }
}
long long query(int row,int index,int** BIT){
    long long count = 0;
    for(int i=index;i>0;i-=(i&(-i))){
        count = (count + BIT[row][i]) % mod;
    }
    return count;
}
int main() {

	int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    int** BIT = new int*[3];
    for(int i=0;i<3;i++)
        BIT[i] = new int[100001]();
    
    int maxval = arr[0];
    update(arr[0],1,BIT,2);
    long long sum = 0;
    for(int i=1;i<n;i++){
        long long a = (query(0,arr[i]-1,BIT) + query(2,arr[i]-1,BIT)) % mod;
        long long b = (query(1,maxval,BIT) - query(1,arr[i],BIT) + query(2,maxval,BIT) - query(2,arr[i],BIT) + mod) % mod;
        sum = (sum + a + b) % mod;
        update(arr[i],a,BIT,1);
        update(arr[i],b,BIT,0);
        update(arr[i],1,BIT,2);
        if(maxval<arr[i])
            maxval = arr[i];
    }
    cout<<sum<<endl;
}