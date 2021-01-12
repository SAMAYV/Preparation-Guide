// https://codeforces.com/contest/570/problem/D

ll const maxn = 500005;
ll depth[maxn], ans[maxn], val[maxn];
vector<pair<ll,ll>> queries[maxn];

ll t = 0, dsu[maxn], sz[maxn];
unordered_map<ll,ll> a[maxn];

void merge(ll v,ll v_set,ll child_set){
    for(auto &x : a[child_set]){
        a[v_set][x.first] ^= x.second;
    }
}
void dfs(ll v,vector<ll>* edges){
    sz[v] = 1;
    if(edges[v].size() == 0){
        dsu[v] = t;
        a[t][depth[v]] = val[v];
        for(auto it:queries[v]){
        	ans[it.second] = 1;
        }
        t++;
        return;
    }
    ll big = maxn-1;
    for(auto &u : edges[v]){
        dfs(u,edges);
        sz[v] += sz[u];
        if(sz[big] < sz[u]){
            big = u;
        }
    }
    dsu[v] = dsu[big];
    a[dsu[v]][depth[v]] ^= val[v];

    for(auto &u : edges[v]){
        if(u != big){
            merge(v,dsu[v],dsu[u]);
        }
    }
    for(auto it:queries[v]){
    	ll p = a[dsu[v]][it.first];
    	if(p == 0 || (p & (p-1)) == 0){
    		ans[it.second] = 1;
    	}
    	else {
    		ans[it.second] = 0;
    	}
    }
}

void depth_calc(vector<ll>* edges,ll curr,ll d){
	depth[curr] = d;
	for(auto it : edges[curr]){
		depth_calc(edges,it,d+1);
	}
}

int main()
{
    i_os;
	ll n,m;
	cin>>n>>m;
	vector<ll> edges[n+1];
	REP(i,2,n+1){
		ll x; cin>>x;
		edges[x].push_back(i);
	}    
	string s;
	cin>>s;
	REP(i,1,n+1){
		ll p = s[i-1]-'a';
		val[i] = (1LL << p);
	}
	depth_calc(edges,1,1);

	REP(i,0,m){
		ll v,p;
		cin>>v>>p;
		queries[v].push_back({p,i});
	}
	dfs(1,edges);	
	REP(i,0,m){
		if(ans[i]) cout<<"Yes\n";
		else cout<<"No\n";
	}
    return 0;
}