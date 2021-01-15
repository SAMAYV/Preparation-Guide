vector<pair<ll,ll>> prufur_code_to_tree(vector<ll> prufur){
	vector<ll> degree(n,1);
	ll n = prufur.size()+2;
	REP(i,0,prufur.size()){
		degree[prufur[i]]++;
	}
	vector<pair<ll,ll>> edges;

	// method-1
	set<ll> leaves;
	REP(i,0,n){
		if(degree[i] == 1) leaves.insert(i);
	}
	REP(i,0,n-2){
		ll curr = *leaves.begin();
		leaves.erase(leaves.begin());
		edges.push_back({prufur[i],curr});
		degree[prufur[i]]--;
		if(degree[prufur[i]] == 1){
			leaves.insert(prufur[i]);
		}
	}
	edges.push_back({*leaves.begin(),n-1});

	// method-2
	ll least_leaf;
	REP(i,0,n){
		if(degree[i] == 1){
			least_leaf = i;
			break;
		}
	}
	ll curr_leaf = least_leaf;
	REP(i,0,n-2){
		edges.push_back({prufur[i],curr_leaf});
		degree[prufur[i]]--;
		if(degree[prufur[i]] == 1 && least_leaf > prufur[i]){
			curr_leaf = prufur[i];
		}
		else {
			least_leaf++;
			while(degree[least_leaf] != 1){
				least_leaf++;
			}
			curr_leaf = least_leaf;
		}
	}
	edges.push_back({curr_leaf,n-1});
	return edges;
}
int main()
{
	return 0;
}