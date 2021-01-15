// https://codeforces.com/contest/1100/problem/F

ll const k = 20;
ll const maxn = 500005;

ll l[maxn],r[maxn],arr[maxn],ans[maxn];
vector<ll> basis[maxn];

ll maxor(vector<ll>& basis){
	ll mask = 0;
	REPI(i,0,k){
		if(basis[i] && !((mask >> i) & 1)){
			mask ^= basis[i];
		}
	}
	return mask;
}

void insertBasis(vector<ll>& basis,ll mask){
	REPI(i,0,k){
		if(!(mask & (1 << i)))
			continue;
		if(!basis[i]){
			basis[i] = mask;
			return;
		}
		mask ^= basis[i]; 
	} 
}
void merge(vector<ll>& a,vector<ll>& b){
	for(auto it:b){
		insertBasis(a,it);
	}
}

void divide_and_conquer(ll L,ll R,vector<ll>& req){
	if(L == R){
		for(auto it:req) ans[it] = arr[L];
		return;
	}
	REP(i,L,R+1){
		basis[i].clear();
		basis[i].resize(k,0);
	}
	ll m = (L + R)/2; 
	insertBasis(basis[m],arr[m]);

	ll l1 = m-1;
	while(l1 >= L){
		basis[l1] = basis[l1+1];
		insertBasis(basis[l1],arr[l1]);
		l1--;
	}
	ll r1 = m+1;
	while(r1 <= R){
		basis[r1] = basis[r1-1];
		insertBasis(basis[r1],arr[r1]);
		r1++;
	}
	vector<ll> req1,req2;
	for(auto it:req){
		if(r[it] <= m){
			req1.push_back(it);
		}
		else if(l[it] > m){
			req2.push_back(it);
		}
		else {
			vector<ll> b1 = basis[l[it]];
			vector<ll> b2 = basis[r[it]];
			merge(b1,b2);
			ans[it] = maxor(b1);
		}
	}
	divide_and_conquer(L,m,req1);
	req1.clear();
	divide_and_conquer(m+1,R,req2);
	req2.clear();
}

int main()
{
	i_os;
	ll n;
	cin>>n;
	REP(i,0,n){
		cin>>arr[i];
	}
	ll q;
	cin>>q;
	vector<ll> req;
	REP(i,0,q){
		cin>>l[i]>>r[i];
		l[i]--; r[i]--;
		req.push_back(i);
	}
	divide_and_conquer(0,n-1,req);
	REP(i,0,q) cout<<ans[i]<<endl;
	return 0;
}
