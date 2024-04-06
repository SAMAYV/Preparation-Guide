bool compare(pair<ll,ll> a,pair<ll,ll> b){
	return a.second < b.second;
}
ll min_manhattan(vector<pair<ll,ll>>& points){
	ll n = points.size();
	REP(i,0,n){
		ll x1 = points[i].first; 
		ll y1 = points[i].second;
		points[i].x = x1 + y1;
		points[i].y = y1 - x1;
	}
	sort(points.begin(),points.end());
	ll mini = 1e9;
	REP(i,1,n){
		mini = min(mini,points[i].first - points[i-1].first);	
	}
	sort(points.begin(),points.end(),compare);
	REP(i,1,n){
		mini = min(mini,points[i].second - points[i-1].second);	
	}
	return mini;
}

// Suppose that we are given a two-dimensional grid that contains n rows and n columns. Each cell is assigned a letter, and our task is to 
// find two cells with the same letter whose distance is minimum, where the distance between cells (x1, y1) and (x2, y2) is |x1-x2| + |y1-y2|.
// This problem can be solved in O(n*n) using manhattan distance.
// Here is the solution in O(n*n*n)

void case_processing(ll n){
	map<ll,ll> um;
	vector<pair<ll,ll>> mp[26];
	REP(i,0,n){
		REP(j,0,n){
			char x;
			cin>>x;
			mp[x - 'A'].push_back({i,j});
			um[x - 'A']++;
		}
	}
	ll mini = 1e9;
	char ch;
	for(auto it:um){
		if(it.second >= n){
			ll p = min_manhattan(mp[it.first]);
			if(p <= mini){
				ch = it.first + 'A';
				mini = p;
			}
		}
		else {
			ll mt = 1e9;
			ll p = it.first;
			ll m = mp[p].size();
			REP(i,0,m){
				REP(j,i+1,m){
					pair<ll,ll> p1 = mp[p][i];
					pair<ll,ll> p2 = mp[p][j];
					mt = min(mt,abs(p1.first - p2.first) + abs(p1.second - p2.second));
				}	
			}
			if(mt < mini){
				ch = it.first + 'A';
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