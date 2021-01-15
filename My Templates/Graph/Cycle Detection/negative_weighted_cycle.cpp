struct Edge {
    ll a, b, cost;
};

void negative_cycle(ll n,ll m,vector<Edge> edges)
{
    vector<ll> dis(n);
    vector<ll> par(n,-1);
    ll x;
    REP(i,0,n){
        x = -1;
        for(Edge e : edges){
            if(dis[e.a] + e.cost < dis[e.b]){
                dis[e.b] = dis[e.a] + e.cost;
                par[e.b] = e.a;
                x = e.b;
            }
        }
    }
    if(x == -1){
        cout<<"No negative cycle found"<<endl;
    } 
    else {
        REP(i,0,n){
            x = par[x];
        }
        vector<ll> cycle;
        for(ll v = x;; v = par[v]){
            cycle.push_back(v);
            if(v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(),cycle.end());
        cout<<"Negative cycle: "<<endl;
        for(auto v : cycle) cout<<v<<" ";
        cout<<endl;
    }
}
 