struct subset {
    ll rank;
    pair<ll,ll> parent;
};
void initialise(subset* s,ll n,vector<ll>& bipartite){
    REP(i,0,n){
        s[i].parent = make_pair(i,0);
        s[i].rank = 0;
        bipartite[i] = true;
    }
}
pair<ll,ll> find(ll v,subset* s){
    if(v != s[v].parent.first){
        ll parity = s[v].parent.second;
        s[v].parent = find(s,s[v].parent.first);
        s[v].parent.second ^= parity;
    }
    return s[v].parent;
}
void add_edge(ll a,ll b,subset* s,vector<ll>& bipartite){
    pair<ll,ll> pa = find(a,s);
    a = pa.first;
    ll x = pa.second;

    pair<ll,ll> pb = find(b,s);
    b = pb.first;
    ll y = pb.second;

    if(a == b){
        if(x == y){
            bipartite[a] = false;
        }
    } 
    else {
        if(s[a].rank < s[b].rank){
            swap(a,b);
        }
        s[b].parent = make_pair(a, x^y^1);
        bipartite[a] &= bipartite[b];
        if(s[a].rank == s[b].rank){
            s[a].rank++;
        }
    }
}
bool is_bipartite(ll v,subset* s){
    return bipartite[find(v,s).first];
}

// Initially we are given an empty graph, it can be added edges, 
// and we have to answer queries of the form "is the connected component containing this vertex bipartite?".

int main()
{
    ll n;
    cin>>n;
    vector<ll> bipartite(n);
    subset s[n];
    initialise(s,n,bipartite);
    REP(i,0,m){
        add_edge(a,b,s,bipartite);
        is_bipartite(v,s);
    }
    return 0;
}