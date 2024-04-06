// https://www.hackerearth.com/problem/algorithm/sallu-bhai-and-ias-8838ac8d/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

ll dp[13][2521][512];
ll pow1[10];
ll LCM = 2520;

ll power(ll a,ll n,ll mod){
	if(n == 0) return 1;
	ll s = power(a,n/2,mod);
	s = (s * s) % mod;
	if(n % 2) s = (s * a) % mod;
	return s;
}

ll memo(ll pos,ll cnt,ll f,ll mask,string& num)
{
    if(pos == num.size()){
    	if(mask == 0) return 0;
    	ll c = 0,p = 0;
        for(int i = 1; i < 10; i++){
        	if((mask >> (i-1)) & 1){
        		if(cnt % i == 0) c++;
        		p++;
        	}
        }
        if(c == p) return 1;
        else return 0;
    }
    if(!f && dp[pos][cnt][mask] != -1){
        return dp[pos][cnt][mask];
    }
    ll res = 0;
    ll LMT = f ? num[pos]-'0' : 9;
    for(int i = 0; i <= LMT; i++){
    	ll v = pow1[i] + cnt;
	    v %= LCM;
        ll val = mask;
        if(i > 0) val |= (1 << (i-1));
	    res += memo(pos+1,v,f & (i == LMT),val,num);
    }
    if(!f) dp[pos][cnt][mask] = res;
    return res;
}

ll solve(string& num)
{
	pow1[0] = 0;
	for(int i = 1; i < 10; i++) pow1[i] = power(i,i,LCM);
    memset(dp,-1,sizeof(dp));
    return memo(0,0,1,0,num);
}

int main()
{
	ll q;
	cin>>q;
	while(q--){
		ll l,r;
		cin>>l>>r;
		string s1 = to_string(r),s2 = to_string(l-1);
		cout<<solve(s1) - solve(s2)<<endl;
	}
    return 0;
}
