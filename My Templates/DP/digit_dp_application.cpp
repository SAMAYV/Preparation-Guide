// https://www.hackerearth.com/problem/algorithm/sallu-bhai-and-ias-8838ac8d/

ll dp[13][2521][512];
ll pow1[10];
ll LCM = 2520;

ll memo(ll pos,ll cnt,ll f,ll mask,string& num)
{
    if(pos == num.size()){
    	if(mask == 0) return 0;
    	ll c = 0,p = 0;
        REP(i,1,10){
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
    REP(i,0,LMT+1){
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
	REP(i,1,10) pow1[i] = power(i,i,LCM);
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
