// sweep line algorithms section in handbook

bool compare(pair<ll,ll> a,pair<ll,ll> b){
	if(a.first == b.first){
		return a.second < b.second;
	}
	else {
		return a.first < b.first;
	}
}

ll closest_pair(vector<pair<ll,ll>>& arr){
	sort(arr.begin(),arr.end(),compare);
	ll d = 1e9;
	ll n = arr.size();
	vector<ll> ycor;
	REP(i,0,n){
		ycor.push_back(arr[i].second);
	}
	REP(i,0,n){
		ll x = arr[i].first;
		ll y = arr[i].second;
		// finding x in range [x-d,x]
		ll p = lower_bound(arr.begin(),arr.begin()+i,x - d) - arr.begin();
		if(p != i){
			// consider for [y-d,y+d] in range p to i-1
			ll p1 = lower_bound(ycor.begin()+p,ycor.begin()+i,y-d) - ycor.begin();
			ll p2 = upper_bound(ycor.begin()+p,ycor.begin()+i,y+d) - ycor.begin() - 1;
			if(p1 != i){
				REP(j,p1,p2+1){
					d = min(sqrtl((x-arr[j].first)*(x-arr[j].first) + (y-arr[j].second)*(y-arr[j].second)));
				}
			}
		}
	}
	return d;
}