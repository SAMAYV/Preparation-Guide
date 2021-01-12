// With dsu on tree we can answer queries of this type:
// How many vertices in the subtree of vertex v has some property in  time (for all of the queries)?
// For example:
// Given a tree, every vertex has color. Query is how many vertices in subtree of vertex v are colored with color c?

// O(nlogn)
// Let st[v] dfs starting time of vertex v, ft[v] be it's finishing time and ver[time] is the vertex which it's starting time is equal to time.

ll const maxn = 1e5 + 5;
ll cnt[maxn], col[maxn];
ll st[maxn], ft[maxn], ver[maxn];

ll timer = 0;
void start_finish_times(ll v,ll p,vector<ll>* edges){
    st[v] = timer;
    ver[timer] = v;
    timer++;
    for(auto u : edges[v]){
        if(u != p){
            start_finish_times(u, v, edges);
        }
    }
    ft[v] = timer++;
}


void dfs(ll v,ll p,bool keep,vector<ll>* edges){
    ll mx = -1, bigChild = -1;
    for(auto u : edges[v]){
       if(u != p && sz[u] > mx){
            mx = sz[u], bigChild = u;
       }
    }
    for(auto u : edges[v]){
        if(u != p && u != bigChild){
            dfs(u, v, 0, edges);                // run a dfs on small childs and clear them from cnt
        }
    }
    if(bigChild != -1){
        dfs(bigChild, v, 1, edges);             // bigChild marked as big and not cleared from cnt
    }
    for(auto u : edges[v]){
    	if(u != p && u != bigChild){
            REP(p,st[u],ft[u]+1){
                cnt[col[ver[p]]]++;
            }
        }
    }
    cnt[col[v]]++;
    
    //  now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(keep == 0){
        REP(p,st[v],ft[v]+1){
            cnt[col[ver[p]]]--;
        }
    }
}