// With dsu on tree we can answer queries of this type:
// How many vertices in the subtree of vertex v has some property in  time (for all of the queries)?
// For example:
// Given a tree, every vertex has color. Query is how many vertices in subtree of vertex v are colored with color c?

// O(nlogn)

ll const maxn = 1e5 + 5;
ll cnt[maxn];
ll col[maxn];
bool big[maxn];

void add(ll v,ll p,ll x,vector<ll>* edges){
    cnt[col[v]] += x;
    for(auto u: edges[v]){
        if(u != p && !big[u]){
            add(u, v, x, edges);
        }
    }
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
            dfs(u, v, 0, edges);        // run a dfs on small childs and clear them from cnt
        }
    }
    if(bigChild != -1){
        dfs(bigChild, v, 1, edges);
        big[bigChild] = 1;              // bigChild marked as big and not cleared from cnt
    }
    add(v, p, 1);
    
    //  now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(bigChild != -1){
        big[bigChild] = 0;
    }
    if(keep == 0){
        add(v, p, -1);
    }
}
