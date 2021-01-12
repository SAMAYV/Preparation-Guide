// https://codeforces.com/contest/600/problem/E

ll const maxn = 1e5 + 5;
ll col[maxn], cnt[maxn], ans[maxn], sz[maxn];
bool big[maxn];
ll max_ct = 0,sum_col = 0;

void getsz(ll v,ll p,vector<ll>* edges){
    sz[v] = 1;                  // every vertex has itself in its subtree
    for(auto u : edges[v]){
        if(u != p){
            getsz(u, v, edges);
            sz[v] += sz[u];     // add size of child u to its parent(v)
        }
    }
}
void add(ll v,ll p,ll x,vector<ll>* edges){
    cnt[col[v]] += x;
    if(max_ct < cnt[col[v]]){
    	max_ct = cnt[col[v]];
    	sum_col = col[v];
    }
    else if(max_ct == cnt[col[v]]){
    	sum_col += col[v];
    }
    for(auto u: edges[v]){
        if(u != p && !big[u]){
            add(u, v, x, edges);
        }
    }
}
void dfs(ll v,ll p,bool keep,vector<ll>* edges){
    ll mx = -1, bigChild = -1;
    for(auto u : edges[v]){
       if(u != p && sz[u] > mx){
          mx = sz[u], bigChild = u;
       }
    }
    for(auto u : edges[v]){
        if(u != p && u != bigChild){
            dfs(u, v, 0, edges);        // run a dfs on small childs and clear them from cnt
        }
    }
    if(bigChild != -1){
        dfs(bigChild, v, 1, edges);
        big[bigChild] = 1;              // bigChild marked as big and not cleared from cnt
    }
    add(v, p, 1, edges);
    
    //  now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    ans[v] = sum_col;

    if(bigChild != -1){
        big[bigChild] = 0;
    }
    if(keep == 0){
        add(v, p, -1, edges);
        max_ct = 0;
        sum_col = 0;
    }
}
int main()
{
	i_os;
	ll n;
	cin>>n;
	REP(i,1,n+1) cin>>col[i];
	vector<ll> edges[n+1];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	getsz(1,0,edges);
	dfs(1,0,0,edges);
	REP(i,1,n+1) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}