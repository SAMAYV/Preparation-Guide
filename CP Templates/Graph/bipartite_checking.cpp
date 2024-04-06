void bipartite(ll n,vector<ll>* edges){
    vector<ll> side(n, -1);
    bool is_bipartite = true;
    queue<ll> q;
    REP(st,0,n){
        if(side[st] == -1){
            q.push(st);
            side[st] = 0;
            while(q.size()){
                ll v = q.front();
                q.pop();
                for(auto u : edges[v]){
                    if(side[u] == -1){
                        side[u] = side[v] ^ 1;
                        q.push(u);
                    } 
                    else {
                        is_bipartite &= (side[u] != side[v]);
                    }
                }
            }
        }
    }
    cout<<(is_bipartite ? "YES" : "NO")<<endl;
}
