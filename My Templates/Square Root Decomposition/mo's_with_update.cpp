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

    vector<Query> queries;
    vector<pair<ll,ll>> upd;
    ll updates = -1;
    REP(i,0,m){
        ll type; cin>>type;
        if(type == 2){
            ll l,x;
            cin>>l>>x;
            upd.push_back({l-1,x});
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
    vector<ll> v = mo_s_algorithm(queries,upd,arr,n);
    REP(i,0,v.size()){
    	cout<<v[i]<<endl;
    }
    return 0;
}
