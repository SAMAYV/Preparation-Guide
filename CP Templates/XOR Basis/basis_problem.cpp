// https://codeforces.com/contest/1101/problem/G

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

int main()
{
	i_os;
    ll n;
    cin>>n;
    ll arr[n];
    ll curr = 0;
    REP(i,0,n){
    	cin>>arr[i];
    	curr ^= arr[i];
    	insertVector(curr);
    }
    if(curr == 0){
    	cout<<-1<<endl;
    }
    else {
    	ll ans = 0;
    	REP(i,0,d){
    		if(basis[i]) ans++;
    	}
    	cout<<ans<<endl;
    }
    return 0;
}