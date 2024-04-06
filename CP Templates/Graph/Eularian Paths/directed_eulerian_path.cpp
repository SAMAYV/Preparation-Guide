void Eularian_Path(set<ll>* edges,ll n){
    vector<ll> out_deg(n,0),in_deg(n,0);
    REP(i,0,n){
        for(auto it:edges[i]){
            out_deg[i]++;
            in_deg[it]++;
        }
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
        if(in_deg[i] != out_deg[i]){
            if(v1 != -1 && v2 != -1){
                bad = 1;
            }
            else if(in_deg[i] - out_deg[i] == 1){
                v1 = i;
            }
            else if(in_deg[i] - out_deg[i] == -1){
                v2 = i;
            }
            else {
                bad = 1;
            }
        }
    }
    if(bad){
        cout<<-1<<endl;
        return;
    }
    else if(v1*v2 < 0){
        cout<<-1<<endl;
        return;   
    }
    if(v1 != -1 && v2 != -1){
        edges[v1].insert(v2);
    }
    stack<ll> st;
    st.push(first);
    vector<ll> res;
    while(st.size()){
        ll v = st.top();
        if(edges[v].size() > 0){
            ll ver = *edges[v].begin();
            edges[v].erase(ver);
            st.push(ver); 
        }
        else {
            res.push_back(v);
            st.pop();
        }
    }
    reverse(res.begin(),res.end());
    if(v1 != -1){
        REP(i,0,res.size()){
            if(res[i] == v1 && res[i + 1] == v2){
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
 