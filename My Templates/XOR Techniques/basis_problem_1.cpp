// https://codeforces.com/contest/959/problem/F

ll const d = 32;
ll basis[d]; 	
ll sz; 

void insertVector(ll mask){
	REP(i,0,d){
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

struct Query {
	ll l,x,idx;
	bool operator<(const Query& q){
		return l < q.l; 
	}
};

bool check(ll x){
	// check if x can be represented using basis
	REP(i,0,d){
		if(((x >> i) & 1) == 0) continue;
		if(!basis[i]) return 0;
		x ^= basis[i];
	}
	return 1;
}

int main()
{
	i_os;
    ll n,q;
    cin>>n>>q;
    ll arr[n+1];
    REP(i,1,n+1){
    	cin>>arr[i];
    }
    int mod = 1e9 + 7;
    vector<Query> queries(q);
    REP(i,0,q){
    	cin>>queries[i].l>>queries[i].x;
    	queries[i].idx = i;
    }
    ll power[n+1];
    power[0] = 1;
    REP(i,1,n+1){
    	power[i] = (power[i-1]*2LL) % mod;
    }
    sort(queries.begin(),queries.end());
    vector<ll> answers(q);
    ll curr = 0;
    REP(i,0,queries.size()){
    	ll ans = 0;
    	while(curr < queries[i].l){
    		curr++;
    		insertVector(arr[curr]);
    	}
    	if(check(queries[i].x)){
    		answers[queries[i].idx] = power[queries[i].l-sz];
    	}
    	else {
    		answers[queries[i].idx] = 0;	
    	}
    }
    REP(i,0,q) cout<<answers[i]<<endl;
    return 0;
}