struct subset {
    ll rank;
    ll parent;
};

ll find(ll x,subset* s){
    if(s[x].parent == x){
        return x;
    }
    s[x].parent = find(s[x].parent,s);
    return s[x].parent;
}

void unio(ll x,ll y,subset* s){
    ll p1 = find(x,s);
    ll p2 = find(y,s);
    if(s[p1].rank == s[p2].rank){
        s[p1].rank++;
        s[p2].parent = p1;
    }
    else if(s[p1].rank > s[p2].rank){
        s[p2].parent = p1;
    }
    else {
        s[p1].parent = p2;  
    }
}

vector<ll> ancestor;
vector<bool> visited;

void dfs(ll v,vector<ll>* edges,vector<vector<ll>>& queries,subset s[]){
    visited[v] = 1;
    ancestor[v] = v;
    for(auto u : edges[v]){
        if(!visited[u]){
            dfs(u,edges,queries,s);
            unio(v,u,s);
            ancestor[find(v,s)] = v;
        }
    }
    for(auto other_node : queries[v]){
        if(visited[other_node]){
            cout<<"LCA of "<<v<<" and "<<other_node<<" is "<<ancestor[find(other_node,s)]<<".\n";
        }
    }
}

void compute_LCAs(ll n,vector<ll>* edges,vector<vector<ll>>& queries){
    ancestor.resize(n);
    visited.assign(n, false);
    subset s[n];
    REP(i,0,n){
        s[i].rank = 0;
        s[i].parent = i;
    }
    dfs(0,edges,queries,s);
}

 