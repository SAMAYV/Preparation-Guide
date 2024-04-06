struct subset {
    pair<ll,ll> parent;
    ll rank;
};

void initialise(subset* s,ll n){
    REP(i,0,n){
        s[i].parent = {i,0};
        s[i].rank = 0;
    }
}

pair<ll,ll> find(ll v,subset* s){
    if(v != s[v].parent.first){
        ll len = s[v].parent.second;
        s[v].parent = find(s[v].parent.first,s);
        s[v].parent.second += len;
    }
    return s[v].parent;
}

void union_sets(ll x,ll y,subset* s){
    ll x = find(x,s).first;
    ll y = find(y,s).first;
    if(x != y){
        if(s[x].rank < s[y].rank){
            swap(x,y);
        }
        s[y].parent = make_pair(x, 1);
        if(s[x].rank == s[y].rank){
            s[x].rank++;
        }
    }
}

int main()
{
    // Maintain the distance between a vertex and the representative of its set 
    // (i.e. the path length in the tree from the current node to the root of the tree).
    // If we don't use path compression, the distance is just the number of recursive calls. But this will be inefficient.
    // However it is possible to do path compression, if we store the distance to the parent as additional information for each node.
    return 0;
}