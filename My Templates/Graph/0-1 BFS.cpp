void bfs01(vector<ll>* edges,ll n){
    vector<ll> d(n, 1e9);
    d[s] = 0;
    deque<ll> q;
    q.push_front(s);
    
    while(q.size()){
        ll v = q.front();
        q.pop_front();
        for(auto it:edges[v]){
            ll u = it.first;
            ll w = it.second;
            if(d[v] + w < d[u]){
                d[u] = d[v] + w;
                if(w == 1)
                    q.push_back(u);
                else
                    q.push_front(u);
            }
        }
    }
}
int main() 
{
    
    return 0; 
}
 