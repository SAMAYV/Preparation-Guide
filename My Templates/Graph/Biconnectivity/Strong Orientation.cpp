vector<ll> tin,low;
ll bridge_cnt,timer;
string orient;
vector<bool> edge_used;

void find_bridges(ll v,vector<pair<ll,ll>>* adj,vector<pair<ll,ll>>& edges)
{
    low[v] = tin[v] = timer++;
    for(auto p : adj[v]){
        if(edge_used[p.second]) 
            continue;
        edge_used[p.second] = 1;
        orient[p.second] = ((v == edges[p.second].first) ? '>' : '<');
        ll nv = p.first;
        if(tin[nv] == -1){ 
            // if nv is not visited yet
            find_bridges(nv,adj,edges);
            low[v] = min(low[v],low[nv]);
            if(low[nv] > tin[v]){
                // a bridge between v and nv
                bridge_cnt++;
            }
        } 
        else {
            low[v] = min(low[v], tin[nv]);
        }
    }
}

void strong_orientation(ll n,ll m,vector<pair<ll,ll>>* adj,vector<pair<ll,ll>>& edges){
    timer = 0;
    bridge_cnt = 0;
    tin.resize(n,-1);
    low.resize(n,-1);
    orient.resize(m);
    edge_used.resize(n,0);
    ll comp_cnt = 0;
    REP(i,0,n){
        if(tin[i] == -1){
            comp_cnt++;
            find_bridges(i,adj,edges);
        }
    }
    printf("%lld\n%s\n", comp_cnt + bridge_cnt, orient.c_str());
}
int main() 
{
    ll n,m;
    cin>>n>>m;
    vector<pair<ll,ll>> adj[n];
    vector<pair<ll,ll>> edges(m);
    REP(i,0,m){
        ll a,b;
        cin>>a>>b;
        a--; b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        edges[i] = {a,b};
    }
    strong_orientation(n,m,adj,edges);
    return 0;
}