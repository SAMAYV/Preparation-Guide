// https://www.hackerrank.com/contests/101hack47/challenges/summing-in-a-tree

int const maxn = 500005;
int depth[maxn], val[maxn], sz[maxn], ans[maxn], cnt[maxn];
int t = 0, zeros = 0, curr = 0; 
bool big[maxn];

void getsz(ll v, vector<ll>* edges){
    sz[v] = 1;              
    for(auto u : edges[v]){
        getsz(u, edges);
        sz[v] += sz[u];     
    }
}
void add(ll v,ll x,vector<ll>* edges){
   	ll prev = cnt[depth[v]];
    cnt[depth[v]] += x;
    if(prev < val[depth[v]] && cnt[depth[v]] >= val[depth[v]]){
    	curr++;
    }
    else if(prev >= val[depth[v]] && cnt[depth[v]] < val[depth[v]]){
    	curr--;
    }
    for(auto u: edges[v]){
        if(!big[u]){
            add(u,x,edges);
        }
    }
}
void dfs(ll v,bool keep,vector<ll>* edges){
    ll mx = -1, bigChild = -1;
    for(auto u:edges[v]){
       	if(sz[u] > mx){
        	mx = sz[u], bigChild = u;
       	}
    }
    for(auto u:edges[v]){
        if(u != bigChild){
            dfs(u,0,edges);        // run a dfs on small childs and clear them from cnt
        }
    }
    if(bigChild != -1){
        dfs(bigChild,1,edges);
        big[bigChild] = 1;              // bigChild marked as big and not cleared from cnt
    }
    add(v,1,edges);
    
    //  now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    ans[v] = curr;

    if(bigChild != -1){
        big[bigChild] = 0;
    }
    if(keep == 0){
        add(v,-1,edges);
    }
}

void depth_calc(vector<ll>* edges,ll curr,ll d){
	depth[curr] = d;
	for(auto it : edges[curr]){
		depth_calc(edges,it,d+1);
	}
}

int main()
{
    i_os;
    ll n,h;
    cin>>n>>h;
    vector<ll> edges[n+1];
    REP(i,1,n){
    	ll x;
    	cin>>x;
    	edges[x].push_back(i);
    }
    REP(i,0,h+1){
    	cin>>val[i];
    	if(val[i] == 0) zeros++;
    }
    depth_calc(edges,0,0);
    getsz(0,edges);
    dfs(0,0,edges);
    ll f = 0;
    REP(i,0,n){
    	f += (ll)ans[i];
    }
    cout<<f + n*zeros<<endl;
    return 0;
}