#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define si size()
#define bk back()
#define popb pop_back()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl "\n"
#define lb lower_bound
#define ub upper_bound
ll mod=1e9+7;
ll power(ll num,ll r){
    if(r==0) return 1;
    if(r==1) return num%mod;
    ll ans=power(num,r/2)%mod;
    if(r%2==0) {
        return (ans*ans)%mod;
    } return (((ans*ans)%mod)*num)%mod;
}
ll modinv(ll num){
    return power(num,mod-2);
}
string s;
ll dp[20][2][5]; //index smaller number_of_nonzero
ll solve ( int index,int smaller,int num){
	if(num>3) return 0;
	if(index==s.length()){
		return 1;
	}

	if(dp[index][smaller][num]!=-1) return dp[index][smaller][num];
	int limit=9;
	if(!smaller) limit=s[index]-'0';
	ll count=0;
	int ns;
	for(int i=0;i<=limit;i++){
		if(i!=limit) ns=1;
		else ns=smaller;
		if(i==0)count+= solve(index+1,ns,num);
		else count+=solve(index+1,ns,num+1);
	}
	dp[index][smaller][num]=count;
	return count;
}
int main(){
	fastio;
	int n;
	cin>>n;
	while(n--){
		string a,b;
		cin>>a>>b;
		int i=a.si-1;
		if(a[i]!='0') a[i]--;
		else {while(a[i]=='0'){a[i]='9'; i--;}
		a[i]--;}
		//cout<<a<<endl;
		memset(dp,-1,sizeof(dp));
		s=b;
		ll y=solve(0,0,0);
		memset(dp,-1,sizeof(dp));
		s=a;
		ll x=solve(0,0,0);
		cout<<y-x<<endl;
	}
	return 0;
}
