// https://codeforces.com/contest/852/problem/I

#define N 100001
ll const sz = 500;

ll arr[20][N], parent[N], depth[N], start[N], ed[N], index[2*N + 1], f[N], a[N], ct[N], answers[N], mp1[N], mp2[N];
vector<ll> edges[N];
Query queries[N];

struct Query {
	ll l, r, idx;
	ll lca;
	bool operator <(const Query& n) const {
		ll p1 = (l/sz);
		ll p2 = (n.l/sz);
		if(p1 == p2){
			if(p1 & 1){
				return r > n.r;
			}
			else {
				return r < n.r;
			}
		}
		return p1 < p2;
	}
};

ll timer = 0;
void euler(ll curr,ll par,ll d){
	start[curr] = timer;
	depth[curr] = d;
	index[timer] = curr;
	parent[curr] = par;
	timer++;
	for(auto it:edges[curr]){
		if(it != par){
			euler(it,curr,d+1);
		}
	}
	ed[curr] = timer;
	index[timer] = curr;
	timer++;
}

void initialize(ll n){
	REP(j,1,n+1){
		arr[0][j] = parent[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = arr[i - 1][j];
			arr[i][j] = arr[i - 1][p];
		}
	}
}

ll LCA(ll x,ll y){
	if(depth[x] > depth[y]){
		swap(x,y);
	}
	ll diff = depth[y] - depth[x];
	REP(i,0,32){
		if((diff >> i) & 1){
			y = arr[i][y];
		}
		if(diff == 0) break;
	}
	REPI(i,0,20){
		if(arr[i][x] != arr[i][y]){
			x = arr[i][x];
			y = arr[i][y];
		}
		if(x == y){
			break;
		}
	}
	if(x != y){
		x = arr[0][x];
		y = arr[0][y];
	}
	return x;
}

ll get_answer = 0;

void update(ll ind,ll curr){
	ll p1 = mp1[a[ind]];
    ll p2 = mp2[a[ind]];
	if(f[ind]){
    	if(curr){
    		mp1[a[ind]]++;
			get_answer += p2;
    	}
    	else {
    		mp1[a[ind]]--;
			get_answer -= p2;
    	}
	}
	else {
    	if(curr){
    		mp2[a[ind]]++;
			get_answer += p1;
    	}
    	else {
    		mp2[a[ind]]--;
			get_answer -= p1;
    	}
	}
}

void mo_s_algorithm(ll n,ll q){
    sort(queries,queries + q);
    REP(i,1,n+1) ct[i] = 0,mp1[i] = 0,mp2[i] = 0;

    ll cur_l = 0, cur_r = -1;

    REP(i,0,q){
        while(cur_l > queries[i].l){
            cur_l--;
            ll ind = index[cur_l];
            if(ct[ind] == 1){
            	update(ind,0);
            }
            else {
            	update(ind,1);
            }
            ct[ind]++;
        }
        while(cur_r < queries[i].r){
            cur_r++;
            ll ind = index[cur_r];
            if(ct[ind] == 1){
            	update(ind,0);
            }
            else {
            	update(ind,1);
            }
            ct[ind]++;
        }
        while(cur_l < queries[i].l){
            ll ind = index[cur_l];
            if(ct[ind] == 2){
            	update(ind,1);
            }
            else {
            	update(ind,0);
            }
            ct[ind]--;
            cur_l++;
        }
        while(cur_r > queries[i].r){
            ll ind = index[cur_r];
            if(ct[ind] == 2){
            	update(ind,1);
            }
            else {
            	update(ind,0);
            }
            ct[ind]--;
            cur_r--;
        }
        if(queries[i].lca != -1){
        	ll ind = index[queries[i].lca];
        	update(ind,1);
        	answers[queries[i].idx] = get_answer;

        	ll p1 = mp1[a[ind]];
        	ll p2 = mp2[a[ind]];
        	if(f[ind]){
        		mp1[a[ind]]--;
        		get_answer -= p2;
        	}
        	else {
        		mp2[a[ind]]--;
        		get_answer -= p1;
        	}
        }
        else {
        	answers[queries[i].idx] = get_answer;
        }
    }
}

int main()
{
	i_os;
	ll n;
	cin>>n;
	REP(i,1,n+1){
		char ch;
		cin>>ch;
		f[i] = ch - '0';
	}
	set<ll> s;
	REP(i,1,n+1){
		cin>>a[i];
		s.insert(a[i]);
	}
	map<ll,ll> mp3;
	ll w = 0;
	for(auto it:s){
		mp3[it] = w++;
	}
	REP(i,1,n+1){
		a[i] = mp3[a[i]];
	}

	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	// Mo's on trees
	euler(1,0,1);

	// LCA
	initialize(n);

	ll q;
	cin>>q;
	REP(i,0,q){
		ll a1,b1;
		cin>>a1>>b1;
		if(start[a1] > start[b1]){
			swap(a1,b1);
		}
		ll p = LCA(a1,b1);
		if(p == a1){
			queries[i].l = start[a1];
			queries[i].r = start[b1];
			queries[i].idx = i;
			queries[i].lca = -1;
		}
		else {
			queries[i].l = ed[a1];
			queries[i].r = start[b1];
			queries[i].idx = i;
			queries[i].lca = start[p];
		}
	}
	mo_s_algorithm(n,q);
	REP(i,0,q) cout<<answers[i]<<"\n";
    return 0;
}
