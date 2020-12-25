/*Given a string 's' consisting of upper case alphabets, i.e. from 'A' to 'Z'. Your task is to find how many strings 't' with length equal to that of 's', also consisting of upper case alphabets are there satisfying the following conditions:
-> String 't' is lexicographical larger than string 's'.
-> When you write both 's' and 't' in the reverse order, 't' is still lexicographical larger than 's'.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
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
    
    // int l;
    // for(l=0;s[l]!='\0';l++);
    // return count(s,l);
    
    int n = strlen(s);
    long long ans=0,val=0;
    for(int i=0;i<n;i++)
    {
        ans = (ans + ((val+1)*('Z'-s[i])) % M) % M;
        val = ((val*26) % M + 'Z'-s[i]) % M;
    }
    int res = ans % M;
    return res;
    
}