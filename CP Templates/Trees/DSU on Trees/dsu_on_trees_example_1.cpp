// https://codeforces.com/contest/600/problem/E
ll const maxn = 1e5 + 5;
ll t = 0, dsu[maxn], col[maxn], sz[maxn], mx[maxn];
ll ans[maxn];
unordered_map<ll,ll> a[maxn];

void merge(ll v,ll v_set,ll child_set){
    for(auto &x : a[child_set]){
        a[v_set][x.first] += x.second;

        if(a[v_set][x.first] > mx[v]){
            mx[v] = a[v_set][x.first];
            ans[v] = x.first;
        }
        else if(a[v_set][x.first] == mx[v]){
            ans[v] += x.first;
        }
    }
}
void dfs(ll v,ll p,vector<ll>* edges){
    sz[v] = 1;
    if(edges[v].size() == 1 && edges[v].back() == p){
        dsu[v] = t;
        a[t][col[v]] = 1;
        ans[v] = col[v];
        mx[v] = 1;
        t++;
        return;
    }
    ll big = maxn-1;
    for(auto &u : edges[v]){
        if(u != p){
            dfs(u,v,edges);
            sz[v] += sz[u];
            if(sz[big] < sz[u]){
                big = u;
            }
        }
    }
    dsu[v] = dsu[big];
    ans[v] = ans[big];
    mx[v] = mx[big];
    
    a[dsu[v]][col[v]]++;
    if(mx[v] < a[dsu[v]][col[v]]){
        ans[v] = col[v];
        mx[v] = a[dsu[v]][col[v]];
    }
    else if(mx[v] == a[dsu[v]][col[v]]){
        ans[v] += col[v];
    }

    for(auto &u : edges[v]){
        if(u != p && u != big){
            merge(v,dsu[v],dsu[u]);
        }
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
    dfs(1,0,edges);
    REP(i,1,n+1) cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}