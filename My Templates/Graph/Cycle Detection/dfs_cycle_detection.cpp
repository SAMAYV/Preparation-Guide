bool dfs(ll ind,ll* state,vector<ll>* edges,map<pair<ll,ll>,bool>& um){
	state[ind] = 1;
	for(auto it : edges[ind]){
		if(state[it] == 1 && um.count({ind,it}) == 0){
			return 1;
		}
		if(state[it] == 0){
			um[{ind,it}] = 1;
			um[{it,ind}] = 1;
			if(dfs(it,state,edges,um)) return 1;
		}
	}
	state[ind] = 2;
	return 0;
}

void Cycle_Detection(ll n,vector<ll>* edges){
	map<pair<ll,ll>,bool> um;
	ll* state = new ll[n];
	REP(i,0,n) state[i] = 0;
	REP(i,0,n){
		if(state[i] == 0){
			if(dfs(i,state,edges,um)){
				cout<<"Cycle found"<<endl;
			}
		}
	}
}

int main() 
{ 
	ll n,e;
	cin>>n>>e;
	vector<ll> edges[n];
	REP(i,0,e){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edges[y-1].push_back(x-1);
	}
	return 0;	
} 
