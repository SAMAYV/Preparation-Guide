bool spfa(ll s,ll n,vector<ll>& d,vector<pair<ll,ll>>* edges){
    d.assign(n,1e9);
    d[s] = 0;

    vector<ll> cnt(n,0);
    vector<bool> inqueue(n,0);
    
    queue<ll> q;
    q.push(s);
    inqueue[s] = 1;

    while(q.size()){
        ll v = q.front();
        q.pop();
        inqueue[v] = 0;
        for(auto edge:edges[v]){
            ll to = edge.first;
            ll len = edge.second;
            if(d[v] + len < d[to]){
                d[to] = d[v] + len;
                if(!inqueue[to]){
                    q.push(to);
                    inqueue[to] = 1;
                    cnt[to]++;
                    if(cnt[to] > n)
                        return 0;  // negative cycle
                }
            }
        }
    }
    return 1;
}
