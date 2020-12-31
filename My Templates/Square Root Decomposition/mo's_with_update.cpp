ll const block_size = 600;

struct Query {
    ll l, r, idx, t, type;
};

bool cmp(Query p,Query q) {
    ll b1 = (p.l / block_size);
    ll b2 = (q.l / block_size);
    return (b1 < b2) || (b1 == b2 && ((b1 & 1) ? (p.r < q.r) : (p.r > q.r))) || (b1 == b2 && p.r == q.r && p.t < q.t);
}

vector<ll> mo_s_algorithm(vector<Query> queries,vector<pair<ll,ll>> v,ll arr[],ll n){
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end(), cmp);

    ll cur_l = 0, cur_r = -1, left = -1;

    for(Query q : queries){
    	while(q.t > left){
    		left++;
    		// perform update 
    	}
    	while(q.t < left){
    		// remove update
    		left--;
    	}
    	if(q.type == 1){
    		continue;
    	}
        while(cur_l > q.l){
            cur_l--;
            // add cur_l 
        }
        while(cur_r < q.r){
            cur_r++;
            // add cur_r 
        }
        while(cur_l < q.l){
            // remove cur_l
            cur_l++;
        }
        while(cur_r > q.r){
            // remove cur_r
            cur_r--;
        }
        answers[q.idx] = ans;
    }
    return answers;
}
int main()
{
	i_os;
    ll n,m;
    cin>>n>>m;
    ll arr[n];
    REP(i,0,n) cin>>arr[i];

    vector<Query> queries(m);
    vector<pair<ll,ll>> upd;
    
    REP(i,0,m){
    	cin>>queries[i].type;
    	if(queries[i].type == 1){
    		cin>>queries[i].l;
    		queries[i].l--;
    		queries[i].r = queries[i].l;
    		ll x;
            cin>>x;
    		upd.push_back({queries[i].l,x});
    		queries[i].t = 1;   		
    	}
    	else {
    		cin>>queries[i].l>>queries[i].r;
    		queries[i].l--;
    		queries[i].r--;
    		queries[i].t = 0;
    	}
    	queries[i].idx = i;
    }
    REP(i,1,m){
    	queries[i].t += queries[i-1].t;
    }
    REP(i,0,m){
    	queries[i].t--;
    }
    vector<ll> v = mo_s_algorithm(queries,upd,arr,n);
    REP(i,0,v.size()){
    	if(queries[i].type == 2) cout<<v[i]<<endl;
    }
    return 0;
}
