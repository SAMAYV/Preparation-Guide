void Eularian_Path(set<ll>* edges,ll n){
    vector<ll> deg(n,0);
    REP(i,0,n){
        deg[i] = edges[i].size();
    }
    ll first = 0;
    while(first < n && !deg[first]){
        first++;
    }
    if(first == n){
        cout<<-1<<endl;
        return;
    }
    ll v1 = -1, v2 = -1;
    bool bad = 0;
    REP(i,0,n){
        if(deg[i] & 1){
            if(v1 == -1) v1 = i;
            else if(v2 == -1) v2 = i;
            else bad = 1;
        }
    }
    if(bad){
        cout<<-1<<endl;
        return;
    }
    if(v1 != -1){
        edges[v1].insert(v2);
        edges[v2].insert(v1);
    }
    stack<ll> st;
    st.push(first);
    vector<ll> res;
    while(st.size()){
        ll v = st.top();
        ll ver,f = 0;
        if(edges[v].size() > 0){
            ver = *edges[v].begin(); 
        }
        else {
            f = 1;
        }
        if(f){
            res.push_back(v);
            st.pop();
        } 
        else {
            edges[v].erase(ver);
            edges[ver].erase(v);
            st.push(ver);
        }
    }
    if(v1 != -1){
        REP(i,0,res.size()){
            if((res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1)){
                vector<ll> res2;
                REP(j,i+1,res.size()){
                    res2.push_back(res[j]);
                }
                REP(j,1,i+1){
                    res2.push_back(res[j]);
                }
                res = res2;
                break;
            }
        }
    }
    REP(i,0,n){
        if(edges[i].size()) bad = 1;
    }
    if(bad){
        cout<<-1<<endl;
    } 
    else {
        for(auto x : res) cout<<x<<" ";
        cout<<endl;
    }
}
