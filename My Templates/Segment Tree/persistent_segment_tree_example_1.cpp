// https://www.spoj.com/problems/DQUERY/

ll const maxn = 300005;

struct Vertex {
    Vertex *l, *r;
    ll sum;
    Vertex(ll val) : l(nullptr), r(nullptr), sum(val){}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0){
        if(l) sum += l->sum;
        if(r) sum += r->sum;
    }
};

Vertex* build(ll start,ll end){
    if(start == end){
        return new Vertex(0);
    }
    ll mid = (start + end)/2;
    return new Vertex(build(start,mid), build(mid+1,end));
}

Vertex* update(Vertex* v,ll start,ll end,ll pos,ll flag){
    if(start == end){
        return new Vertex(v->sum+flag);
    }
    ll mid = (start + end)/2;
    if(pos <= mid){
        return new Vertex(update(v->l, start, mid, pos, flag), v->r);
    }
    else {
        return new Vertex(v->l, update(v->r, mid+1, end, pos, flag));
    }
}

ll query(Vertex* v,ll start,ll end,ll left,ll right){
    if(left > end || right < start){
        return 0;
    }
    if(left <= start && end <= right){
        return v->sum;
    }
    ll mid = (start + end)/2;
    return query(v->l, start, mid, left, right)
         + query(v->r, mid+1, end, left, right);
}

int main()
{
	i_os;
	ll n;
	cin>>n;
	ll arr[n];
	REP(i,0,n){
		cin>>arr[i];
	}
	vector<Vertex*> roots;
	roots.push_back(build(0,n));
	map<ll,ll> mp1;
	REP(i,0,n){
		Vertex* p = roots.back();
		if(mp1.count(arr[i])){
			p = update(p,0,n,mp1[arr[i]],-1);
		}
		roots.push_back(update(p,0,n,i,1));
		mp1[arr[i]] = i;
	}
	ll m;
	cin>>m;
	while(m--){
		ll l,r;
		cin>>l>>r;
		cout<<query(roots[r],0,n,l-1,r-1)<<endl;
	}
	return 0;
}