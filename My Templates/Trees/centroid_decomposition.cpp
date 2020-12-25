struct centroid {
    vector<vector<ll>> edges;
    vector<bool> vis;
    vector<ll> par;
    vector<ll> sz;
    ll n;
 
    void init(ll s){
        n = s;
        edges = vector<vector<ll>>(n, vector<ll>());
        vis = vector<bool>(n, 0);
        par = vector<ll>(n);
        sz = vector<ll>(n);
    }
 
    void edge(ll a,ll b){
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
 
    ll find_size(ll v,ll p = -1) {
        if(vis[v]) return 0;
        sz[v] = 1;
        for(ll x: edges[v]){
            if(x != p){
                sz[v] += find_size(x, v);
            }
        }
        return sz[v];
    }
 
    ll find_centroid(ll v,ll p,ll n) {
        for(ll x: edges[v]){
            if(x != p){
                if(!vis[x] && sz[x] > n/2){
                    return find_centroid(x, v, n);
                }
            }
        }
        return v;
    }
 
    void init_centroid(ll v = 0,ll p = -1){
        find_size(v);
        ll c = find_centroid(v, -1, sz[v]);
        vis[c] = true;
        par[c] = p; 
        for(ll x: edges[c]){
            if(!vis[x]){
                init_centroid(x, c);
            }
        }
    }
};

centroid ct;

int main() 
{
    ll n;
    cin>>n;
    ct.init(n);
    REP(i,0,n){
        ll x,y;
        cin>>x>>y;
        ct.edge(x,y);
    }
    ct.init_centroid();
    return 0; 
}
 