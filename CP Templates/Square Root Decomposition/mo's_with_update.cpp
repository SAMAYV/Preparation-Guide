ll const maxn = 1e5 + 5;
ll const maxq = 1e5 + 5;
ll const block_size = 2500;  // n^(2/3)
ll const P = 2500; // n^(2/3)

ll answers[maxq];

struct Query {
    ll l, r, idx, t, type;
};

struct Update {
    ll l, val;
};

bool cmp(Query p,Query q){
    ll b1 = (p.l / block_size);
    ll b2 = (q.l / block_size);
    return (b1 < b2) || (b1 == b2 && ((b1 & 1) ? (p.r < q.r) : (p.r > q.r))) || (b1 == b2 && p.r == q.r && p.t < q.t);
}

bool cmp1(Query p,Query q){
    ll b1 = (p.t / P);
    ll b2 = (q.t / P);
    ll b11 = (p.l / P);
    ll b22 =  (q.l / P);
    return (b1 < b2) || (b1 == b2 && b11 < b22) || (b1 == b2 && b11 == b22 && p.r < q.r);
}

void mo_s_algorithm(vector<Query>& queries,vector<Update>& updates,ll* arr,ll n){
    sort(queries.begin(),queries.end(),cmp);

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
}
int main()
{
	i_os;
    ll n,m;
    cin>>n>>m;
    ll arr[n];
    REP(i,0,n) cin>>arr[i];

    vector<Query> queries;
    vector<Update> updates;
    ll upd_ct = -1;
    REP(i,0,m){
        ll type; 
        cin>>type;
        if(type == 2){
            Update u;
            cin>>u.l>>u.x;
            u.l--;
            updates.push_back(u);
            upd_ct++;
        }
        else {
            Query q;
            cin>>q.l>>q.r;
            q.l--;
            q.r--;
            q.t = upd_ct;
            q.idx = queries.size();
            queries.push_back(q);
        }
    }
    mo_s_algorithm(queries,updates,arr,n);
    REP(i,0,queries.size()) cout<<answers[i]<<endl;
    return 0;
}
