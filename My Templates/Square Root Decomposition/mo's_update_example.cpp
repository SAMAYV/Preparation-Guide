// https://www.spoj.com/problems/XXXXXXXX/

ll const maxn = 1e5 + 5;
ll const maxq = 1e5 + 5;
ll const block_size = 2500;  // n^(2/3)
ll P;

ll answers[maxq], compressed[maxn + maxq], ct[maxn + maxq];

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

ll sum = 0;

void increase(ll val){
	ct[val]++;
	if(ct[val] == 1){
		sum += compressed[val];
	}
}
void decrease(ll val){
	ct[val]--;
	if(ct[val] == 0){
		sum -= compressed[val];
	}
}


void mo_s_algorithm(vector<Query>& queries,vector<Update>& updates,ll* arr,ll n){
    sort(queries.begin(),queries.end(),cmp1);

    ll cur_l = 0, cur_r = -1, left = -1;

    for(Query q : queries){
    	// cout<<q.l<<" "<<q.r<<" "<<q.idx<<" "<<q.t<<endl;
    	while(q.t > left){
    		left++;
    		// if current updated index is in [cur_l,cur_r]
    		if(updates[left].l >= cur_l && updates[left].l <= cur_r){
    			decrease(arr[updates[left].l]);
    			increase(updates[left].val);
    		}
    		swap(updates[left].val, arr[updates[left].l]);
    	}
    	while(q.t < left){
    		if(updates[left].l >= cur_l && updates[left].l <= cur_r){
    			decrease(arr[updates[left].l]);
    			increase(updates[left].val);
    		}
    		swap(updates[left].val, arr[updates[left].l]);
    		left--;
    	}
        while(cur_l > q.l){
            cur_l--;
            increase(arr[cur_l]);
        }
        while(cur_r < q.r){
            cur_r++;
            increase(arr[cur_r]);
        }
        while(cur_l < q.l){
            decrease(arr[cur_l]);
            cur_l++;
        }
        while(cur_r > q.r){
            decrease(arr[cur_r]);
            cur_r--;
        }
        answers[q.idx] = sum;
    }
}
int main()
{
	i_os;
    ll n;
    cin>>n;
    P = pow(n,2.0/3.0);
    ll arr[n];
    set<ll> s;
    REP(i,0,n){
    	cin>>arr[i];
    	s.insert(arr[i]);
    }
    vector<Query> queries;
    vector<Update> updates;
    ll upd_ct = -1;
    ll m;
    cin>>m;
    REP(i,0,m){
        char type;
        cin>>type;
        if(type == 'U'){
            Update u;
            cin>>u.l>>u.val;
            s.insert(u.val);
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
    ll curr = 0;
    map<ll,ll> mp;
    for(auto it:s){
    	mp[it] = curr;
    	compressed[curr] = it;
    	curr++;
    }
    for(Update &u:updates){
    	u.val = mp[u.val];
    }
    REP(i,0,n){
    	arr[i] = mp[arr[i]];
    }
    mo_s_algorithm(queries,updates,arr,n);
    REP(i,0,queries.size()) cout<<answers[i]<<endl;
    return 0;
}