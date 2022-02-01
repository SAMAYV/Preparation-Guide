ll timer = 1, SCC = 0;
vector<bool> vis,onStack;
vector<ll> in,low;
stack<ll> st;

void dfs(ll node,vector<ll>* edges)
{
    vis[node] = 1;
    in[node] = low[node] = timer++;
    onStack[node] = 1;
    st.push(node);
    for(auto u:edges[node]){
        if(vis[u] && onStack[u]){
            low[node] = min(low[node],in[u]);
        }
        else {
            if(!vis[u]){
                dfs(u,edges);
                if(onStack[u]){
                    low[node] = min(low[node],low[u]);       
                } 
            }
        }
    }
    if(in[node] == low[node]){
        SCC++;
        cout<<"SCC #"<<SCC<<endl;
        while(st.size() && st.top() != node){
            ll u = st.top();
            st.pop(); 
            onStack[u] = 0;
            cout<<u<<" ";
        }
        cout << st.top() << "\n";
        st.pop();
    }
}

void tarjan(ll n,vector<ll>* edges){
    timer = 1;
    SCC = 0;
    vis.resize(n,0);
    onStack.resize(n,0);
    in.resize(n,0);
    low.resize(n,0);
    REP(i,0,n){
        if(!vis[i]) dfs(i,edges);
    }
}
