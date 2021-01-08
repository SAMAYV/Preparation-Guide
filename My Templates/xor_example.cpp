// https://codeforces.com/contest/895/problem/C
// https://codeforces.com/blog/entry/68953

const int N = 1e5 + 10;
const int MAX_A = 70;
const int TOTAL_PRIMES = 19;
const int MOD = 1e9 + 7;
 
int n;
int poss[MAX_A + 1][2];
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
int mask[MAX_A + 1];
int dp[MAX_A + 1][1 << TOTAL_PRIMES];
 
int main() 
{
	cin >> n;
 
	for (int i = 1; i <= MAX_A; i++) poss[i][0] = 1;
 
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
 
		int tmp = poss[a][0];
		poss[a][0] = (poss[a][0] + poss[a][1]) % MOD;
		poss[a][1] = (poss[a][1] + tmp) % MOD;
	}
 
	for (int i = 1; i <= MAX_A; i++) {
		for (int p = 0; p < TOTAL_PRIMES; p++) {
			int cnt = 0;
			int at = i;
 
			while (at % primes[p] == 0) {
				at /= primes[p];
				cnt++;
			}
 
			if (cnt & 1) mask[i] |= (1 << p);
		}
	}
 
	int max_mask = 1 << TOTAL_PRIMES;
	dp[0][0] = 1;
	
	for (int at = 1; at <= MAX_A; at++)
		for (int msk = 0; msk < max_mask; msk++) {
			dp[at][msk] = dp[at - 1][msk] * 1LL * poss[at][0] % MOD;
 
			dp[at][msk] += dp[at - 1][msk ^ mask[at]] * 1LL * poss[at][1] % MOD;
			dp[at][msk] %= MOD;
		}
 
	cout << (dp[MAX_A][0] + MOD - 1) % MOD << endl;
 
	return 0;
}