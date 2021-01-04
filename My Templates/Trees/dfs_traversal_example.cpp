// https://codeforces.com/contest/1328/problem/E

ll const maxn = 200005;
ll in[maxn],out[maxn],parent[maxn],depth[maxn];
ll timer = 0;

void dfs(ll curr,ll par,vector<ll>* edges,ll d){
	in[curr] = timer++;
	parent[curr] = par;
	depth[curr] = d;
	for(auto it:edges[curr]){
		if(it != par){
			dfs(it,curr,edges,d+1);
		}
	}
	out[curr] = timer++;
}

int main()
{
	i_os;
	ll n,m;
	cin>>n>>m;
	vector<ll> edges[n];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edges[y-1].push_back(x-1);
	}
	dfs(0,-1,edges,0);
	REP(i,0,m){
		ll k;
		cin>>k;
		vector<ll> v(k);
		REP(j,0,k){
			cin>>v[j];
		}
		ll ver = 0;
		for(auto &it:v){
			it--;
			if(depth[it] > depth[ver]) ver = it;
		}
		for(auto &it:v){
			if(it != 0 && it != ver){
				it = parent[it];
			}
		}
		bool ok = 1;
		for(auto it:v){
			ok &= (in[ver] >= in[it] && out[ver] <= out[it]);
		}
		if(ok) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}