// sweep line algorithms in handbook

// idx is index of 0-based array
ll point_query(ll idx,ll* tree){
    ll ret = 0;
    for(++idx; idx > 0; idx -= (idx & -idx)){
        ret += tree[idx];
    }
    return ret;
}
void add(ll idx,ll val,ll* tree,ll n){
    for(++idx; idx <= n; idx += (idx & -idx)){
        tree[idx] += val;
    }
}
bool compare(vector<ll> a,vector<ll> b){
	if(a[1] == b[1]){
		return a[0] < b[0];
	}
	else {
		return a[1] < b[1];
	}
}
ll intersection_points(vector<vector<ll>>& points){
	// sort by x coordinate
	// 0: beginning of a horizontal line
	// 2: end of a horizontal line
	// 1: vertical line
	vector<vector<ll>> arr;
	ll n = points.size();
	REP(i,0,n){
		if(points[i][0] == points[i][1]){
			arr.push_back({1,points[i][1],points[i][2],points[i][3]})
		}
		else {
			arr.push_back({0,points[i][0],points[i][2]});
			arr.push_back({2,points[i][1],points[i][2]});
		}
	}
	sort(arr.begin(),arr.end(),compare);
	set<ll> s;
	REP(i,0,n){
		s.insert(points[i][2]);
		s.insert(points[i][3]);
	}
	ll m = s.size();
	ll tree[m+3] = {0};
	map<ll,ll> mp;
	ll curr = 0;
	for(auto it:s){
		mp[it] = curr;
		curr++;
	}
	ll ans = 0;
	REP(i,0,arr.size()){
		ll y = mp[arr[i][2]];
		if(arr[i][0] == 0){
			add(y,1,tree,m+1);
		}
		else if(arr[i][0] == 1){
			ll y1 = mp[arr[i][3]];
			ans += point_query(y1,tree) - point_query(y-1,tree);
		}
		else {
			add(y,-1,tree,m+1);
		}
	}
	return ans;
}