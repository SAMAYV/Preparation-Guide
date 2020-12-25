struct lca_lift {
    const ll lg = 24;
    ll n;
    vector<ll> depth;
    vector<vector<ll>> edges;
    vector<vector<ll>> lift;
  
    void init(ll sz){
        n = sz;
        depth = vector<ll>(n);
        edges = vector<vector<ll>>(n, vector<ll>());
        lift = vector<vector<ll>>(n, vector<ll>(lg, -1));
    }
 
    void edge(ll a,ll b){
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
 
    void attach(ll node_to_attach,ll node_to_attach_to){
        ll a = node_to_attach, b = node_to_attach_to;
        edge(a, b);
 
        lift[a][0] = b;
 
        REP(i,1,lg){
            if(lift[a][i - 1] == -1) lift[a][i] = -1;
            else lift[a][i] = lift[lift[a][i - 1]][i - 1];
        }
        depth[a] = depth[b] + 1;
    }
 
    void init_lift(ll v = 0){
        depth[v] = 0;
        dfs(v, -1);
    }
 
    void dfs(ll v,ll par){
        lift[v][0] = par;
        REP(i,1,lg){
            if(lift[v][i - 1] == -1) lift[v][i] = -1;
            else lift[v][i] = lift[lift[v][i - 1]][i - 1];
        }
        for(ll x: edges[v]){
            if(x != par){
                depth[x] = depth[v] + 1;
                dfs(x, v);
            }
        }
    }
 
    ll get(ll v,ll k){
        REPI(i,0,lg){
            if(v == -1) return v;
            if((1 << i) <= k){
                v = lift[v][i];
                k -= (1 << i);
            }
        }
        return v;
    }
 
    ll get_lca(ll a,ll b){
        if(depth[a] < depth[b]) swap(a, b);
        ll d = depth[a] - depth[b];
        ll v = get(a, d);
        if(v == b){
            return v;
        } 
        else {
            REPI(i,0,lg){
                if(lift[v][i] != lift[b][i]){
                    v = lift[v][i];
                    b = lift[b][i];
                }
            }
            return lift[b][0];
        }
    }
  
    ll get_dist(ll a,ll b){
        ll v = get_lca(a, b);
        return depth[a] + depth[b] - 2 * depth[v];
    }
};

lca_lift lca;

int main() 
{
    ll n;
    cin>>n;
    lca.init(n);
    REP(i,0,n){
        ll x,y;
        cin>>x>>y;
        ct.edge(x,y);
    }
    lca.init_lift();
    return 0; 
}
 