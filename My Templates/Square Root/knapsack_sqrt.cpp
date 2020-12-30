// Suppose that we are given a list of integer weights whose sum is n. 
// Our task is to find out all sums that can be formed using a subset of the weights.
// We can make the algorithm more efficient by using the fact that there are at most O(sqrt(n)) distinct weights.

vector<ll> knapsack(ll n,ll arr[]){
	map<ll,ll> um;
	ll sum = 0;
	REP(i,0,n){
		um[arr[i]]++;
		sum += arr[i];
	}	
	vector<pair<ll,ll>> v;
	for(auto it:um){
		v.push_back(it);
	}
	sort(v.begin(),v.end());
	vector<bool> arr(sum+1,0);
	arr[0] = 1;

	for(auto it:v){
		ll val = it.first;
		ll ct = it.second;
		vector<ll> ct_used(sum+1,0);
		REP(i,0,sum+1-val){
			if(arr[i] && !arr[i+val] && ct_used[i] < ct){
				arr[i+val] = 1;
				ct_used[i+val] = ct_used[i] + 1;
			}
		}
	}
	vector<ll> all_sums;
	REP(i,0,sum+1){
		if(arr[i]) all_sums.push_back(i);
	}
	return all_sums;
}
int main() 
{ 
	ll n;
	cin>>n;
	ll arr[n];
	REP(i,0,n){
		cin>>arr[i];
	}
	vector<ll> all_sums = knapsack(n,arr);
	for(auto it:all_sums) cout<<it<<" ";
	cout<<endl;
	return 0;	
} 