#include <bits/stdc++.h>
using namespace std;
#define ll long long
int DP(int* arr,int n,int d){
    int mod = pow(10,5) + 1;
    int** dp = new int*[2*d+1]; // index d+1 for common diff -1
    for(int i=0;i<2*d+1;i++){
        dp[i] = new int[n+1]();
    }
    for(int r=0;r<2*d+1;r++){
        dp[r][0] = 0;
        dp[r][1] = 1;
    }
    ll count = 2;
    for(int c=2;c<n+1;c++){
        int curr = arr[c-1];
        for(int k=c-1;k>0;k--){
            int val = arr[k-1];
            int diff = curr-val;
            if(diff>=0)
                dp[diff][c] += dp[diff][k];
            else
                dp[d-diff][c] += dp[d-diff][k];
        }
        for(int r=0;r<2*d+1;r++){
            count = (count + dp[r][c]) % mod;
        }
        count = (count + 1) % mod;
        for(int r=0;r<2*d+1;r++){
            dp[r][c] += 1;
        }
    }
    // for(int r=0;r<2*d+1;r++){
    //     for(int c=1;c<n+1;c++)
    //         cout<<dp[r][c]<<" ";
    //     cout<<endl;
    // }
    return count;
}
int numofAP(int *arr, int N){
    int max = INT_MIN;
    int min = INT_MAX;
    for(int i=0;i<N;i++){
        if(arr[i]>max)
            max = arr[i];
        if(arr[i]<min)
            min = arr[i];
    }
    return DP(arr,N,max-min);
}


int main(){
    int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++)
        cin>arr[i];
    cout<<numofAP(arr,n);
}