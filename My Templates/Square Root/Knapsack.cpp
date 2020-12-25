int main() 
{ 
	ll k;
	cin>>k;
	unordered_map<ll,ll> um;
	ll sum = 0;
	REP(i,0,k){
		ll x;
		cin>>x;
		um[x]++;
		sum += x;
	}	
	vector<pair<ll,ll>> v;
	for(auto it:um){
		v.push_back({it.first,it.second});
	}
	sort(v.begin(),v.end());

	pair<bool,ll> arr[sum+1];
	REP(i,0,sum+1){
		arr[i].first = 0;
		arr[i].second = 0;
	}
	arr[0].first = 1;

	REP(i,0,v.size()){
		ll val = v[i].first;
		REP(j,1,sum+1){
			if(arr[j].first == 0){
				if(j-val >= 0 && arr[j-val].first == 1 && arr[j-val].second + 1 <= v[i].second){
					arr[j].first = 1;
					arr[j].second = arr[j-val].second + 1;
				}
			}
		}
		REP(j,1,sum+1){
			arr[j].second = 0;
		}
	}
	REP(i,0,sum+1){
		if(arr[i].first) cout<<i<<" ";
	}
	cout<<endl;
	return 0;	
} 