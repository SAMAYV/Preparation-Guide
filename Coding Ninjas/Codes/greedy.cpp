#include<bits/stdc++.h>
using namespace std;
struct interval {
    int st;
    int ed;
    int cost;
};
bool compare(interval i1,interval i2){
    return i1.ed < i2.ed; 
}
int max(int a,int b){
    return a > b ? a : b;
}
int main()
{
    //Write your code here
    int n;
    cin>>n;
    interval* a = new interval[n];
    for(int i=0;i<n;i++){
        cin>>a[i].st>>a[i].ed>>a[i].cost;
    }
    sort(a,a+n,compare);
    int* dp = new int[n];
    dp[0] = a[0].cost;
    for(int i=1;i<n;i++){
        int j;
        for(j=i-1;j>=0;j--){
            if(a[i].st >= a[j].ed){
                break;
            }
        }
        if(j < 0){
            dp[i] = max(a[i].cost,dp[i-1]);
        }
        else {
            dp[i] = max(dp[i-1],a[i].cost + dp[j]);
        }
    }
    cout<<dp[n-1];
}
