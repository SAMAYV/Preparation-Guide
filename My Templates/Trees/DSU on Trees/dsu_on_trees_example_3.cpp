// https://codeforces.com/contest/246/problem/E

ll const maxn = 500005;
ll depth[maxn], ans[maxn], val[maxn];
vector<pair<ll,ll>> queries[maxn];

ll t = 0, dsu[maxn], sz[maxn];
map<ll,set<ll>> a[maxn];

void merge(ll v,ll v_set,ll child_set){
    for(auto &x : a[child_set]){
        for(auto &it : x.second){
        	a[v_set][x.first].insert(it);
        }
    }
}
void dfs(ll v,vector<ll>* edges){
    sz[v] = 1;
    if(edges[v].size() == 0){
        dsu[v] = t;
        a[t][depth[v]].insert(val[v]);
        for(auto it:queries[v]){
        	ans[it.second] = 0;
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
    a[dsu[v]][depth[v]].insert(val[v]);

    for(auto &u : edges[v]){
        if(u != big){
            merge(v,dsu[v],dsu[u]);
        }
    }
    for(auto it:queries[v]){
    	ll p = a[dsu[v]][it.first + depth[v]].size();
    	ans[it.second] = p;
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
	ll n;
	cin>>n;
	vector<ll> edges[n+1];
	vector<ll> roots;
	set<string> v;
	string arr[n+1];
	
	REP(i,1,n+1){
		cin>>arr[i];
		v.insert(arr[i]);
		ll x;
		cin>>x;
		if(x == 0){
			roots.push_back(i);
		}
		else {
			edges[x].push_back(i);
		}
	}    
	map<string,ll> mp1;
	ll curr = 0;
	for(auto it:v){
		mp1[it] = curr++;
	}
	REP(i,1,n+1){
		val[i] = mp1[arr[i]];
	}
	for(auto it:roots){
		depth_calc(edges,it,1);
	}
	ll m;
	cin>>m;
	REP(i,0,m){
		ll v,p;
		cin>>v>>p;
		queries[v].push_back({p,i});
	}
	for(auto it:roots){
		dfs(it,edges);
	}	
	REP(i,0,m){
		cout<<ans[i]<<endl;
	}
    return 0;
}