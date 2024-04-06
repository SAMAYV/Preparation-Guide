// https://codeforces.com/contest/1364/problem/D

map<pair<ll,ll>,ll> mp;
void dfs_tree(ll curr,ll par,vector<ll>* edges,vector<ll>* tree,vector<ll>* back,vector<ll>& vis,vector<ll>& depth,ll d){
	vis[curr] = 1;
	depth[curr] = d;
	for(auto it:edges[curr]){
		if(it == par){
			continue;
		}
		if(!mp.count({curr,it}) && !mp.count({it,curr})){
			mp[{curr,it}] = 1;
			if(vis[it]){
				back[curr].push_back(it);
			}
		}
		if(!vis[it]){
			tree[curr].push_back(it);
			dfs_tree(it,curr,edges,tree,back,vis,depth,d+1);
		}
	}
}
void traverse(vector<ll>* tree,ll curr,ll f,vector<ll>& v){
	if(!f) v.push_back(curr);
	for(auto it:tree[curr]){
		traverse(tree,it,(f^1),v);
	}
}
bool cycle(vector<ll>& v,ll curr,ll dest,vector<ll>* tree){
	if(curr == dest){
		v.push_back(dest);
		return 1;
	}
	for(auto it:tree[curr]){
		if(cycle(v,it,dest,tree)){
			v.push_back(curr);
			return 1;
		}
	}
	return 0;
}
int main()
{
	i_os;
	ll n,m,k;
	cin>>n>>m>>k;
	vector<ll> edges[n+1],tree[n+1],back[n+1];
	REP(i,0,m){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	vector<ll> vis(n+1,0);
	vector<ll> depth(n+1,0);
	dfs_tree(1,0,edges,tree,back,vis,depth,1);
	ll ver1 = -1,ver2 = -1,d = 0;
	REP(i,1,n+1){
		for(auto it:back[i]){
			if(ver1 == -1){
				ver1 = it;
				ver2 = i;
				d = depth[ver2] - depth[ver1];
			}
			else {
				if(depth[i] - depth[it] < d){
					ver1 = it;
					ver2 = i;
					d = depth[ver2] - depth[ver1];
				}
			}
		}
	}
	if(ver1 != -1){
		vector<ll> v;
		cycle(v,ver1,ver2,tree);
		reverse(v.begin(),v.end());
		if(v.size() <= k){
			cout<<2<<endl;
			cout<<v.size()<<endl;
			for(auto it:v) cout<<it<<" ";
			cout<<endl;
		}
		else {
			ll i = 0,ct = 0;
			cout<<1<<endl;
			while(ct < (k+1)/2){
				cout<<v[i]<<" ";
				i += 2;
				ct++;
			}
			cout<<endl;
		}
	}
	else {
		cout<<1<<endl;
		vector<ll> v;
		traverse(tree,1,0,v);
		if(v.size() >= (k+1)/2){
			REP(i,0,(k+1)/2) cout<<v[i]<<" ";
			cout<<endl;
		}
		else {
			map<ll,ll> mp1;
			REP(i,0,v.size()) mp1[v[i]] = 1;
			ll ct = 0,curr = 1;
			while(ct < (k+1)/2){
				if(!mp1.count(curr)){
					cout<<curr<<" ";
					ct++;
				}
				curr++;
			}
			cout<<endl;
		}
	}
	return 0;
}