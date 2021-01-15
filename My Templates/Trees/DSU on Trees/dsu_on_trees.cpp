// With dsu on tree we can answer queries of this type:
// How many vertices in the subtree of vertex v has some property in  time (for all of the queries)?
// For example:
// Given a tree, every vertex has color. Query is how many vertices in subtree of vertex v are colored with color c?

// O(nlogn)

ll const maxn = 1e5 + 5;
vector<ll> *vec[maxn];
ll cnt[maxn], col[maxn], sz[maxn];

void getsz(ll v,ll p,vector<ll>* edges){
    sz[v] = 1;                  // every vertex has itself in its subtree
    for(auto u : edges[v]){
        if(u != p){
            getsz(u, v, edges);
            sz[v] += sz[u];     // add size of child u to its parent(v)
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
           dfs(u, v, 0, edges);
       }
    }
    if(bigChild != -1){
        dfs(bigChild, v, 1, edges); 
        vec[v] = vec[bigChild];
    }
    else {
        vec[v] = new vector<ll>();
    }
    vec[v]->push_back(v);
    cnt[col[v]]++;
    for(auto u : edges[v]){
        if(u != p && u != bigChild){
            for(auto x : *vec[u]){
               cnt[col[x]]++;
               vec[v]->push_back(x);
           }
        }
    }
    //  now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    //  note that in this step *vec[v] contains all of the subtree of vertex v.
    if(keep == 0){
        for(auto u : *vec[v]){
            cnt[col[u]]--;
        }
    }
}