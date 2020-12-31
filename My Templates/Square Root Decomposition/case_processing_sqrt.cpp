void case_processing(ll n)
{
	vector<vector<pair<ll,ll>>> edges(n,vector<pair<ll,ll>>(n));
	REP(i,0,n){
		REP(j,0,n){
			if(i+1 < n) edges[i][j].push_back({i+1,j});
			if(j+1 < n) edges[i][j].push_back({i,j+1});
			if(i-1 >= 0) edges[i][j].push_back({i-1,j});
			if(j-1 >= 0) edges[i][j].push_back({i,j-1});
		}
	}
	map<char,ll> um;
	vector<pair<ll,ll>> vt[26];

	REP(i,0,n){
		REP(j,0,n){
			char x;
			cin>>x;
			mp[x - 'A'].push_back({i,j});
			um[x]++;
		}
	}
	ll mini = 1e9;
	char ch;
	for(auto it:um){
		if(it.second >= n){
			ll p = compute(vt,edges,it.first,n);
			if(p <= mini){
				ch = it.first;
				mini = p;
			}
		}
		else {
			ll mt = 1e9;
			ll p = it.first - 'A';
			REP(i,0,vt[p].size()){
				REP(j,i+1,vt[p].size()){
					pair<ll,ll> p1 = vt[p][i];
					pair<ll,ll> p2 = vt[p][j];
					mt = min(mt,abs(p1.first - p2.first) + abs(p1.second - p2.second));
				}	
			}
			if(mt < mini){
				ch = it.first;
				mini = mt;
			}
		}
	}
	cout<<ch<<" "<<mini<<endl;
}
int main() 
{ 
	ll n;
	cin>>n;
	case_processing(n);
	return 0;	 
} 