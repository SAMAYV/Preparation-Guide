// https://codeforces.com/contest/1334/problem/E

ll power(ll a,ll n,ll c){
	if(n == 0) return 1 % c;
	ll s = power(a,n/2,c);
	s = (s * s) % c;
	if(n % 2) s = (s * a) % c;
	return s;
}

ll const maxn = 1e5;
ll const mod = 998244353;
int main()
{
	i_os;
	ll d,q;
	cin>>d>>q;
	vector<ll> primes;
	REP(i,2,sqrt(d) + 1){
		ll c = 0;
		while(d % i == 0){
			d /= i;
			c++;
		}
		if(c) primes.push_back(i);
	}
	if(d > 1) primes.push_back(d);
	vector<ll> fact(maxn,1),modinv(maxn,1);
	REP(i,1,maxn){
		fact[i] = fact[i-1]*i;
		fact[i] %= mod;
		modinv[i] = modinv[i-1]*power(i,mod-2,mod);
		modinv[i] %= mod;
	}
	while(q--){
		ll a,b;
		cin>>a>>b;
		ll p = __gcd(a,b);
		ll div = a/p;
		ll mul = b/p;
		vector<ll> v1,v2;
		ll tot1 = 0,tot2 = 0;
		for(auto it:primes){
			ll c = 0;
			while(div % it == 0){
				div /= it;
				c++;
				tot1++;
			}
			if(c) v1.push_back(c);
			ll c1 = 0;
			while(mul % it == 0){
				mul /= it;
				c1++;
				tot2++;
			}
			if(c1) v2.push_back(c1);
		}
		ll ans1 = fact[tot1];
		ll ans2 = fact[tot2];
		for(auto it:v1){
			ans1 *= modinv[it];
			ans1 %= mod;
		}
		for(auto it:v2){
			ans2 *= modinv[it];
			ans2 %= mod;
		}
		ll ans = (ans1*ans2) % mod;
		cout<<ans<<endl;
	}
	return 0;
}
