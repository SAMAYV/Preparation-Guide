#include<bits/stdc++.h>
using namespace std;
#define ll long long
int mod = 1e9 + 7;
int count(char* s,int n){
	
	ll* power = new ll[n+2];
	power[0] = 1;
	for(int i=1;i<n+2;i++)
		power[i] = (power[i-1]*26) % mod;

	ll** dp = new ll*[n+1];
	for(int i=0;i<=n;i++)
		dp[i] = new ll[2]();

    int c = 1;
	while(c<=n){
        int k = c % 2;
		for(int r=n;r>0;r--){
			if(r > c)
				continue;
			if(r==c){
				dp[r][k] = 'Z' - s[r-1];
				continue;
			}
			ll val = (((power[c-r-1]*('Z'-s[r-1])) % mod)*('Z'-s[c-1])) % mod;
			dp[r][k] = (((val + dp[r+1][k]) % mod + dp[r][1^k]) % mod - dp[r+1][1^k] + mod) % mod;
		}
        c++;
	}
	return dp[1][n % 2];
}

int countStrings(char* s) {
    /* Don't write main().
       Don't read input, it is passed as function argument.
       Return output and don't print it.
       Taking input and printing output is handled automatically.
   */
    int l;
    for(l=0;s[l]!='\0';l++);
    return count(s,l);
}
