struct Query {
	ll l,r,c;
};

struct subset {
	ll parent;
};

void initialise(subset* s,ll n){
	REP(i,0,n){
		s[i].parent = i;
	}
}

ll find(ll x,subset* s){
	if(s[x].parent == x){
		return x;
	}
	s[x].parent = find(s[x].parent,s);
	return s[x].parent;
}

int main()
{
	// We have a segment of length L, each element initially has the color 0. 
	// We have to repaint the subarray [l,r] with the color c for each query (l,r,c). 
	// At the end we want to find the final color of each cell. 
	// We assume that we know all the queries in advance, i.e. the task is offline.
	ll L;
	cin>>L;
	subset s[L];
	initialise(subset,L);
	// parent[v] stores the pointer to the next cell which further leads to the representative of the set which is an unpainted cell
	
	ll q;
	cin>>q;
	vector<ll> answer(L,0);
	vector<Query> query(q);

	REPI(i,0,q){
    	ll l = query[i].l;
    	ll r = query[i].r;
    	ll c = query[i].c;
    	for(ll v = find(l,s); v <= r; v = find(v,s)){
        	answer[v] = c;
        	s[v].parent = v + 1;
    	}
	}
	return 0;
}