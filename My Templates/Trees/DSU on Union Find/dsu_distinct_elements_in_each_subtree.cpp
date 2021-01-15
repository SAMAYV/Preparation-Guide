struct subset {
    ll parent;
};

void initialise(set<ll>* lst,subset* s,ll n,vector<ll>& values) {
    REP(i,0,n){
        lst[i].insert(values[i]);
        s[i].parent = i;
    }
}

ll find(ll x,subset* s){
    if(s[x].parent == x){
        return x;
    }
    s[x].parent = find(s[x].parent,s);
    return s[x].parent;
}

void unio(ll a,ll b,subset* s,set<ll>* lst){
    a = find(a,s);
    b = find(b,s);
    if(a != b){
        if(lst[a].size() < lst[b].size()){
            swap(a, b);
        }
        while(lst[b].size()){
            ll v = *lst[b].begin();
            lst[b].erase(lst[b].begin());
            s[v].parent = a;
            lst[a].insert(v);
        }
    }
}

void dfs(ll curr,ll par,subset* s,set<ll>* lst,vector<ll>& answer,vector<ll>& values){
    for(auto it:edges[curr]){
        if(it != par){
            dfs(it,curr,s,lst,answer,values);
            unio(curr,it,s,lst);
        }
    }
    answer[curr] = lst[find(curr,s)].size();
}

void distinct_ele_in_each_subtree(vector<ll>* edges,ll n,vector<ll>& values){
    set<ll> lst[n];
    subset s[n];
    initialise(lst,s,n,values);
    vector<ll> answer(n,0);
    dfs(0,-1,s,lst,answer,values);
}

int main()
{
    // we are given a tree, each leaf has a number assigned (same number can appear multiple times on different leaves). 
    // We want to compute the number of different numbers in the subtree for every node of the tree.
    ll n;
    cin>>n;
    vector<ll> edges[n];
    vector<ll> values(n);
    distinct_ele_in_each_subtree(edges,n,values);
    return 0;
}