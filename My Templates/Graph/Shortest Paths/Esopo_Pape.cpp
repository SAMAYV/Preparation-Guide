void esopo_pape(ll st,vector<ll>& dis,vector<ll>& par,ll n,vector<pair<ll,ll>>* edges){
    dis.assign(n,1e9);
    par.assign(n,-1);
    dis[st] = 0;
    vector<ll> m(n,2);
    deque<ll> q;
    q.push_back(st);

    while(q.size()){
        ll u = q.front();
        q.pop_front();
        m[u] = 0;
        for(auto e : edges[u]){
            if(dis[e.first] > dis[u] + e.second){
                dis[e.first] = dis[u] + e.second;
                par[e.first] = u;
                if(m[e.first] == 2){
                    m[e.first] = 1;
                    q.push_back(e.first);
                } 
                else if(m[e.first] == 0){
                    m[e.first] = 1;
                    q.push_front(e.first);
                }
            }
        }
    }
}
// The algorithm performs usually quite fast. In most cases even faster than Dijkstra's algorithm. 
// However there exist cases for which the algorithm takes exponential time.
