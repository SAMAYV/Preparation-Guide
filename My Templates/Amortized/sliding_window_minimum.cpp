void sliding_window_min(ll n,ll k,ll arr[]){
	deque<ll> q;
	q.push_back(arr[0]);
	REP(i,1,k){
		while(q.size() > 0 && q.back() >= arr[i]){
			q.pop_back();
		}
		q.push_back(arr[i]);
	}
	vector<ll> v;
	v.push_back(q.front());
	REP(i,k,n){
		if(q.size() > 0 && q.front() == arr[i - k]){
			q.pop_front();
		}
		while(q.size() > 0 && q.back() >= arr[i]){
			q.pop_back();
		}
		q.push_back(arr[i]);
		v.push_back(q.front());	
	}
	for(auto it:v) cout<<it<<" ";
	cout<<endl;
}
int main() 
{ 
	ll n,k;
	cin>>n>>k;
	ll arr[n];
	REP(i,0,n){
		cin>>arr[i];
	}	
	sliding_window_min(n,k,arr);
	return 0;	 
} 