void dfs(ll v,vector<ll>* edges,vector<ll>& parent) 
{
    for(auto u : edges[v]){
        if(u != parent[v]){
            parent[u] = v;
            dfs(u);
        }
    }
}

vector<ll> tree_to_prufur_code(vector<ll>* edges,ll n){
	vector<ll> degree(n,0);
	REP(i,0,n){
		degree[i] = edges[i].size();
	}
	vector<ll> prufur(n-2,0);

	// method-1
	set<ll> leaves;
	REP(i,0,n){
		if(degree[i] == 1) leaves.insert(i);
	}
	vector<ll> marked(n,0);
	REP(i,0,n-2){
		ll curr = *leaves.begin();
		leaves.erase(leaves.begin());
		marked[curr] = 1;
		for(auto it:edges[curr]){
			if(!marked[it]){
				prufur[i] = it;
				degree[it]--;
				if(degree[it] == 1) leaves.insert(it);
				break;
			}
		}
	}

	// method-2
	vector<ll> parent(n,-1);
	dfs(n-1);
	ll least_leaf;
	REP(i,0,n){
		if(degree[i] == 1){
			least_leaf = i;
			break;
		}
	}
	ll curr_leaf = least_leaf;
	REP(i,0,n-2){
		prufur[i] = curr_leaf;
		ll v = parent[curr_leaf];
		degree[v]--;
		if(degree[v] == 1){
			if(least_leaf < v){
				least_leaf++;
				while(degree[least_leaf] != 1){
					least_leaf++;
				}
				curr_leaf = least_leaf;
			}
			else {
				curr_leaf = v;
			}
		}
	}
	return prufur;
}
