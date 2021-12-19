// https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/S
// medium

ll const d = 32;
ll basis[d]; 	
ll sz; 

void insertVector(ll mask){
	REPI(i,0,d){
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

ll query(ll k){
	ll mask = 0;
	ll tot = 1 << sz;
	REPI(i,0,d){
		if(basis[i]){
			ll p = tot/2;
			if((k > p && ((mask >> i) & 1) == 0) || (k <= p && ((mask >> i) & 1 == 1))){
				mask ^= basis[i];
			}
			if(k > p) k -= p;
			tot /= 2;
		}
	}
	return mask;
}

int main()
{
	i_os;
    ll n;
    cin>>n;
    REP(i,0,n){
    	ll t,x;
    	cin>>t>>x;
    	if(t == 1){
    		insertVector(x);
    	}
    	else {
    		cout<<query(x)<<endl;
    	}
    }
    return 0;
}
