/*You are given:

a positive integer n,
an integer k, 1<=k<=n,
an increasing sequence of k integers 0 < s1 < s2 < ... < sk <= 2n.

What is the number of proper bracket expressions of length 2n with opening brackets appearing in positions s1, s2,...,sk?*/
#include <bits/stdc++.h>
using namespace std;
int DP(bool* mark,int k,int n){
    int** dp = new int*[n+1];
    for(int i=0;i<n+1;i++)
        dp[i] = new int[n+1]();
    for(int r=0;r<n+1;r++)
        dp[r][0] = 1;
    
    for(int r=1;r<n+1;r++){
        for(int c=1;c<n+1;c++){
            int noofbrackets = r+c;
            if(r<c)
                dp[r][c] = 0;
            else if(r==c){
                if(mark[noofbrackets]==true){
                    dp[r][c] = 0;
                }   
                else {
                    dp[r][c] = dp[r][c-1];
                }
            }
            else if(r>c){
                if(mark[noofbrackets]==true){
                    dp[r][c] = dp[r-1][c];
                }
                else {
                    dp[r][c] = dp[r-1][c] + dp[r][c-1];
                }
            }
        }
    }
    return dp[n][n];
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        bool* arr = new bool[2*n + 1];
        for(int i=0;i<2*n + 1;i++)
            arr[i] = false;
        for(int i=0;i<k;i++){
            int a;
            cin>>a;
            arr[a] = true;
        }
        if(arr[0]==true)
            cout<<0<<endl;
        else
            cout<<DP(arr,k,n)<<endl;
    }
    return 0;
}
