// Given a set S of size 1≤n≤105 with elements 0≤ai<220. Find the number of distinct integers that can be represented 
// using xor over the set of the given elements.

const ll N = 1e5 + 10, LOG_A = 20;
ll basis[LOG_A];
ll sz;

void insertVector(ll mask){
	REP(i,0,LOG_A){
		if(((mask >> i) & 1) == 0){
			continue;
		} 
		if(!basis[i]){
			basis[i] = mask;
			++sz;	
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
	cout<<(1LL << sz)<<endl;
	return 0;
}