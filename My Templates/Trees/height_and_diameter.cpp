void dfs(vector<ll>& parent,vector<ll>* edges,ll curr,ll prev,vector<ll>& diameter,vector<ll>& height)
{
	ll max1 = 0, max2 = 0;
	for(auto it : edges[curr]){
		if(it == prev)
			continue;
		parent[it] = curr;
		dfs(parent,edges,it,curr,diameter,height);

		height[curr] = max(height[curr],height[it]);
		if(height[it] >= max1){
			max2 = max1;
			max1 = height[it];
		} 
		else if(height[it] > max2){
			max2 = height[it];
		}
	}
	height[curr] += 1; 
	diameter[curr] = max1 + max2;
}
void height_and_diameter(ll n,vector<ll>* edges){
	vector<ll> parent(n,-1);
	vector<ll> diameter(n,0);
	vector<ll> height(n,0);
	dfs(parent,edges,0,-1,diameter,height);
	REP(i,0,n){
		cout<<i+1<<" "<<height[i]<<" "<<diameter[i]<<endl;
	}
}
int main() 
{ 
	ll n;
	cin>>n;
	vector<ll> edges[n];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edges[y-1].push_back(x-1);
	}
	height_and_diameter(n,edges);
	return 0;	
} 
