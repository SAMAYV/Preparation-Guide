// https://codeforces.com/contest/940/problem/F

struct Query {
    ll l, r, idx, t;
};

ll const P = 2500; // n^(3/2)

// Complexity is O(n*P) for movement of t, l and O(n*n*n/(P*P)) for movement of r.
// Final Complexity is O(n^(5/3))

bool cmp(Query p,Query q) {
    ll b1 = (p.t / P);
    ll b2 = (q.t / P);
    ll b11 = (p.l / P);
    ll b22 =  (q.l / P);
    return (b1 < b2) || (b1 == b2 && b11 < b22) || (b1 == b2 && b11 == b22 && p.r < q.r);
}

ll mp[200010];
ll rev_mp[100005],temp[100005],answers[100005];

void increase(ll val){
	ll p = mp[val];
	rev_mp[p]--;
	rev_mp[p+1]++;
	mp[val]++;
}

void decrease(ll val){
	ll p = mp[val];
	rev_mp[p]--;
	rev_mp[p-1]++;
	mp[val]--;
}

void mo_s_algorithm(vector<Query>& queries,vector<pair<ll,ll>>& v,ll arr[],ll n){
    sort(queries.begin(),queries.end(),cmp);
    ll cur_l = 0, cur_r = -1, left = -1;
    ll bound = 2*(sqrt(n) + 1);

    for(Query q : queries){
    	while(q.t < left){
    		// remove update
    		if(v[left].first >= cur_l && v[left].first <= cur_r){
    			decrease(arr[v[left].first]);
    			increase(v[left].second);
    		}
    		swap(v[left].second,arr[v[left].first]);
    		left--;
    	}
    	while(q.t > left){
    		left++;
    		// perform update
    		if(v[left].first >= cur_l && v[left].first <= cur_r){
    			decrease(arr[v[left].first]);
    			increase(v[left].second);
    		}
    		swap(v[left].second,arr[v[left].first]);
    	}
        while(cur_l > q.l){
            cur_l--;
            // add cur_l
            increase(arr[cur_l]);
        }
        while(cur_r < q.r){
            cur_r++;
            // add cur_r
         	increase(arr[cur_r]);
        }
        while(cur_l < q.l){
            // remove cur_l
            decrease(arr[cur_l]);
            cur_l++;
        }
        while(cur_r > q.r){
            // remove cur_r
            decrease(arr[cur_r]);
            cur_r--;
        }
        REP(i,1,bound + 1){
        	if(rev_mp[i] == 0){
        		answers[q.idx] = i;
        		break;
        	}
        }
    }
}

int main()
{
	i_os;
    ll n,m;
    cin>>n>>m;
    ll arr[n];
    set<ll> s;
    REP(i,0,n){
    	cin>>arr[i];
    	s.insert(arr[i]);	
    } 
    vector<Query> queries;
    vector<pair<ll,ll>> upd;
    ll updates = -1;
    REP(i,0,m){
    	ll type; cin>>type;
    	if(type == 2){
    		ll l,x;
    		cin>>l>>x;
    		upd.push_back({l-1,x});
    		s.insert(x);
    		updates++;
    	}
    	else {
    		Query q;
    		cin>>q.l>>q.r;
    		q.l--;
    		q.r--;
    		q.t = updates;
    		q.idx = queries.size();
    		queries.push_back(q);
    	}
    }
    // index compress
    map<ll,ll> um;
    ll curr = 0;
    for(auto it:s){
    	um[it] = curr++;
    }
    REP(i,0,n){
    	arr[i] = um[arr[i]];
    }
    REP(i,0,upd.size()){
    	upd[i].second = um[upd[i].second];
    }

    // mo's
    mo_s_algorithm(queries,upd,arr,n);
    REP(i,0,queries.size()){
    	cout<<answers[i]<<endl;
    }
	return 0;
}
