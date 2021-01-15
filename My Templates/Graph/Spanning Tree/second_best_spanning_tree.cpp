struct Edge {
    ll s, e, w, id;
    bool operator<(const struct Edge& other){
        return w < other.w;
    }
};
struct subset {
    ll rank;
    ll parent;
};
ll find(ll x,subset* s){
    if(s[x].parent == x){
        return x;
    }
    s[x].parent = find(s[x].parent,s);
    return s[x].parent;
}
void unio(ll x,ll y,subset* s){
    ll p1 = find(x,s);
    ll p2 = find(y,s);
    if(s[p1].rank == s[p2].rank){
        s[p1].rank++;
        s[p2].parent = p1;
    }
    else if(s[p1].rank > s[p2].rank){
        s[p2].parent = p1;
    }
    else {
        s[p1].parent = p2;  
    }
}

ll res = 0, l = 21;
vector<Edge> edges;
vector<ll> h, parent, size, present;
vector<vector<pair<ll,ll>>> adj,dp;
vector<vector<ll>> up;

pair<ll,ll> combine(pair<ll,ll> a, pair<ll,ll> b){
    vector<ll> v = {a.first, a.second, b.first, b.second};
    ll topTwo = -3, topOne = -2;
    for(ll c : v){
        if(c > topOne){
            topTwo = topOne;
            topOne = c;
        } 
        else if (c > topTwo && c < topOne){
            topTwo = c;
        }
    }
    return {topOne,topTwo};
}
void dfs(ll u,ll par,ll d){
    h[u] = 1 + h[par];
    up[u][0] = par;
    dp[u][0] = {d, -1};
    for(auto v : adj[u]){
        if(v.first != par){
            dfs(v.first, u, v.second);
        }
    }
}
pair<ll,ll> lca(ll u,ll v){
    pair<ll,ll> ans = {-2,-3};
    if(h[u] < h[v]){
        swap(u, v);
    }
    REPI(i,0,l){
        if(h[u] - h[v] >= (1 << i)){
            ans = combine(ans, dp[u][i]);
            u = up[u][i];
        }
    }
    if(u == v){
        return ans;
    }
    REPI(i,0,l){
        if(up[u][i] != -1 && up[v][i] != -1 && up[u][i] != up[v][i]){
            ans = combine(ans, combine(dp[u][i], dp[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }
    ans = combine(ans,combine(dp[u][0],dp[v][0]));
    return ans;
}
void intitialise(ll n){
    parent.resize(n+1);
    REP(i,1,n+1){
        parent[i] = i;
    }
    size.resize(n+1,1);
    up.resize(n+1,vector<ll>(l,-1));
    dp.resize(n+1,vector<pair<ll,ll>>(l));
    h.resize(n+1,0);
    present.resize(n+1,0);
    adj.resize(n+1,vector<pair<ll,ll>>());
}
ll Kruskal(ll n,ll m){
    subset s[n];
    REP(i,0,n){
        s[i].rank = 0;
        s[i].parent = i;
    }
    ll res = 0;
    sort(edges.begin(),edges.end());
    REP(i,0,m){
        ll a = edges[i].s;
        ll b = edges[i].e;
        ll w = edges[i].w;
        ll id = edges[i].id;
        if(find(a,s) != find(b,s)){
            unio(a,b,s); 
            adj[a].push_back({b,w});
            adj[b].push_back({a,w});
            present[id] = 1;
            res += w;
        }
    }
    return res;
}
void LCA_spanning_tree(ll n){
    REP(i,1,l){
        REP(j,1,n+1){
            if(up[j][i - 1] != -1){
                ll v = up[j][i - 1];
                up[j][i] = up[v][i - 1];
                dp[j][i] = combine(dp[j][i - 1], dp[v][i - 1]);
            }
        }
    }
}
ll second_best_spanning_tree(ll m,ll res){
    ll ans = 1e18;
    REP(i,0,m){
        ll id = edges[i].id;
        ll w = edges[i].w;
        if(!present[id]){
            auto rem = lca(edges[i].s, edges[i].e);
            if(rem.first != w){
                if(ans > res + w - rem.first){
                    ans = res + w - rem.first;
                }
            } 
            else if(rem.second != -1){
                if(ans > res + w - rem.second){
                    ans = res + w - rem.second;
                }
            }
        }
    }
    return ans;
}
int main(void) 
{
    ll n,m;
    cin>>n>>m;
    intitialise(n);
    REP(i,0,m){
        ll a,b,w;
        cin>>a>>b>>w; // 1-indexed
        edges.push_back({a,b,w,i});
    }
    ll res = Kruskal(n,m);
    dfs(1, 0, 0);
    LCA_spanning_tree(n);
    ll ans = second_best_spanning_tree(m,res);
    cout<<ans<<"\n";
    return 0;
}