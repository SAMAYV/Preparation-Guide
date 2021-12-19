// Find count of numbers in range [L, R] such that sum of its digits is a prime number.

// dp[i][0][sum]→ count of suffixes that can be formed starting from index i, whose digits add up to sum
// dp[i][1][sum]→ count of suffixes that can be formed starting from index i, whose digits add up to sum such that the formed suffix is not greater than corresponding suffix in input string

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

ll digit_dp(string ss){
    ll n = ss.size();
    
    ll dp[20][2][200];
    memset(dp,0,sizeof(dp));

    // empty suffixes having sum=0
    dp[n][0][0] = 1;
    dp[n][1][0] = 1;
 
    REPI(i,0,n){
        REP(tight,0,2){
            REP(sum,0,200){
                if(tight){
                    for(ll d = 0; d <= ss[i] - '0'; d++){
                        dp[i][1][sum] += (d == ss[i]-'0') ? dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
                    }
                }
                else {
                    for(ll d = 0; d < 10; d++){
                        dp[i][0][sum] += dp[i+1][0][sum-d];
                    }
                }
            }
        }
    }
    ll ans = 0;
    REP(i,0,200){
        if(isPrime(i)){
            ans += dp[0][1][i];
        }
    }
    return ans;
}
