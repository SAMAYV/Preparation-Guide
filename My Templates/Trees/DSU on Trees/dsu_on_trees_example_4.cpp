// https://codeforces.com/contest/375/problem/D

ll const maxn = 1e5 + 5;
ll depth[maxn], ans[maxn], val[maxn];
vector<pair<ll,ll>> queries[maxn];

ll t = 0, dsu[maxn], sz[maxn];
indexed_set a[maxn];
unordered_map<ll,ll> temp[maxn];

void merge(ll v,ll v_set,ll child_set){
    for(auto &x : a[child_set]){
        auto it = a[v_set].find({temp[v_set][x.second], x.second});
        if(it != a[v_set].end()){
        	a[v_set].erase(it);
        	a[v_set].insert({x.first + temp[v_set][x.second], x.second});
        	temp[v_set][x.second] += x.first;
        }
        else {
        	a[v_set].insert(x);
        	temp[v_set][x.second] = x.first;
        }
    }
}
void dfs(ll v,ll p,vector<ll>* edges){
    sz[v] = 1;
    if(edges[v].size() == 1 && edges[v].back() == p){
        dsu[v] = t;
        a[t].insert({1,val[v]});
        temp[t][val[v]] = 1;
        for(auto it:queries[v]){
    		ll p = a[dsu[v]].order_of_key({it.first,-1});
    		ans[it.second] = a[dsu[v]].size() - p;
    	}
        t++;
        return;
    }
    ll big = maxn-1;
    for(auto &u : edges[v]){
    	if(u == p){
    		continue;
    	}
        dfs(u,v,edges);
        sz[v] += sz[u];
        if(sz[big] < sz[u]){
            big = u;
        }
    }
    dsu[v] = dsu[big];
    
    auto it = a[dsu[v]].find({temp[dsu[v]][val[v]],val[v]});
    if(it != a[dsu[v]].end()){
        a[dsu[v]].erase(it);
        a[dsu[v]].insert({1 + temp[dsu[v]][val[v]],val[v]});
        temp[dsu[v]][val[v]] += 1;
    }
    else {
       	a[dsu[v]].insert({1,val[v]});
        temp[dsu[v]][val[v]] = 1;
    }

    for(auto &u : edges[v]){
        if(u != big && u != p){
            merge(v,dsu[v],dsu[u]);
        }
    }
    for(auto it:queries[v]){
    	ll p = a[dsu[v]].order_of_key({it.first,-1});
    	ans[it.second] = a[dsu[v]].size() - p;
    }
}

int main()
{
    i_os;
	ll n,m;
	cin>>n>>m;
	REP(i,1,n+1) cin>>val[i];
	vector<ll> edges[n+1];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	REP(i,0,m){
		ll v,k;
		cin>>v>>k;
		queries[v].push_back({k,i});
	}
	dfs(1,0,edges);
	REP(i,0,m) cout<<ans[i]<<endl;
    return 0;
}