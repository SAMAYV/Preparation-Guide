// https://codeforces.com/contest/1287/problem/D

ll const maxn = 2005;
ll c[maxn],parent[maxn],arr[maxn],size[maxn];

bool check(ll curr,vector<ll>* edges){
	size[curr] = 1;
	for(auto it:edges[curr]){
		if(!check(it,edges)) return 0;
		size[curr] += size[it];
	}
	if(c[curr] >= size[curr]) return 0;
	return 1;
}
vector<pair<ll,ll>> dfs(ll curr,vector<ll>* edges){
	vector<pair<ll,ll>> v;
	ll shift = 0;
	for(auto it:edges[curr]){
		vector<pair<ll,ll>> p = dfs(it,edges);
		for(auto it:p) v.push_back({it.first+shift,it.second});
		shift = v.back().first;
	}
	v.insert(v.begin()+c[curr],{c[curr]+1,curr});
	REP(i,c[curr]+1,v.size()) v[i].first++;
	return v;
}
int main()
{
	i_os;
	ll n;
	cin>>n;
	REP(i,1,n+1){
		cin>>parent[i]>>c[i];
	}
	vector<ll> edges[n+1];
	ll root;
	REP(i,1,n+1){
		if(parent[i] != 0){
			edges[parent[i]].push_back(i);
		}
		else {
			root = i;
		}
	}
	if(!check(root,edges)){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	vector<pair<ll,ll>> v = dfs(root,edges);
	ll ans[n+1];
	for(auto it:v) ans[it.second] = it.first;
	REP(i,1,n+1) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}