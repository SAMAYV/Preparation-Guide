// Given a set S of size 1≤n≤105 with elements 0≤ai<220. What is the maximum possible xor of the elements of some subset of S?

const ll N = 1e5 + 10, LOG_A = 20;
ll basis[LOG_A];

void insertVector(ll mask){
	REPI(i,0,LOG_A){
		if(((mask >> i) & 1) == 0) continue;
		if(!basis[i]){
			basis[i] = mask;
			return;
		}
		mask ^= basis[i];
	}
}

int main() 
{
	ll n;
	cin>>n;
	ll arr[n];
	REP(i,0,n){
		cin>>arr[i];
		insertVector(a);
	}
	ll ans = 0;
	REPI(i,0,LOG_A){
		if(!basis[i]) continue;
		if((ans >> i) & 1) continue;
		ans ^= basis[i];
	}
	cout<<ans<<endl;
	return 0;
}