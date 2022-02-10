// https://codeforces.com/contest/895/problem/C
// https://codeforces.com/blog/entry/68953

const ll N = 1e5 + 10;
const ll MAX_A = 70;
const ll TOTAL_PRIMES = 19;
const ll MOD = 1e9 + 7;
 
int poss[MAX_A + 1][2];
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
int mask[MAX_A + 1];
int dp[MAX_A + 1][1 << TOTAL_PRIMES];
 
int main()
{
	ll n
	cin>>n;
	REP(i,1,MAX_A+1){
		poss[i][0] = 1;	
	} 
	REP(i,0,n){
		ll a;
		cin>>a;
		ll tmp = poss[a][0];
		poss[a][0] = (poss[a][0] + poss[a][1]) % MOD;
		poss[a][1] = (poss[a][1] + tmp) % MOD;
	}
	REP(i,1,MAX_A+1){
		REP(p,0,TOTAL_PRIMES){
			ll cnt = 0;
			ll at = i;
			while(at % primes[p] == 0){
				at /= primes[p];
				cnt++;
			}
			if(cnt & 1) mask[i] |= (1 << p);
		}
	}
	ll max_mask = 1 << TOTAL_PRIMES;
	dp[0][0] = 1;
	REP(at,1,MAX_A+1){
		REP(mask,0,max_mask){
			dp[at][msk] = dp[at - 1][msk] * 1LL * poss[at][0] % MOD;
			dp[at][msk] += dp[at - 1][msk ^ mask[at]] * 1LL * poss[at][1] % MOD;
			dp[at][msk] %= MOD;
		}
	}
	cout<<(dp[MAX_A][0] + MOD - 1) % MOD<<endl;
	return 0;
}