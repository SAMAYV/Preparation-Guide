// Editorial at www.blog.anudeep.com/persistent-segment-trees-explained-with-spoj-problems
// Question at http://www.spoj.com/problems/COT/
// O( (N+M) * log N )

ll const maxn = 100005;
ll values[maxn], depth[maxn], parent[maxn], lca[20][maxn];
ll maxi = 0;

struct Vertex {
    Vertex *l, *r;
    ll sum;
    Vertex(ll val) : l(nullptr), r(nullptr), sum(val){}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0){
        if(l) sum += l->sum;
        if(r) sum += r->sum;
    }
};

Vertex* roots[maxn];

Vertex* build(ll start,ll end){
    if(start == end){
        return new Vertex(0);
    }
    ll mid = (start + end)/2;
    return new Vertex(build(start,mid), build(mid+1,end));
}

Vertex* update(Vertex* v,ll start,ll end,ll pos){
    if(start == end){
        return new Vertex(v->sum+1);
    }
    ll mid = (start + end)/2;
    if(pos <= mid){
        return new Vertex(update(v->l, start, mid, pos), v->r);
    }
    else {
        return new Vertex(v->l, update(v->r, mid+1, end, pos));
    }
}

ll find_kth(Vertex* a,Vertex* b,Vertex* c,Vertex* d,ll start,ll end,ll k){
    if(start == end){
        return start;
    }
    ll mid = (start + end)/2, left_count = a->l->sum + b->l->sum - c->l->sum - d->l->sum;
    if(left_count >= k){
        return find_kth(a->l, b->l, c->l, d->l, start, mid, k);
    }
    return find_kth(a->r, b->r, c->r, d->r, mid+1, end, k-left_count);
}

void dfs(vector<ll>* edges,ll curr,ll par,ll d,ll* arr){
	depth[curr] = d;
	parent[curr] = par;
	roots[curr] = update(roots[par],0,maxi,arr[curr]);
	for(auto it : edges[curr]){
		if(it != par){
			dfs(edges,it,curr,d + 1,arr);
		}
	}
}
void initialize(vector<ll>* edges,ll n,ll* arr){
	dfs(edges,1,0,1,arr);
	REP(j,1,n+1){
		lca[0][j] = parent[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = lca[i - 1][j];
			lca[i][j] = lca[i - 1][p];
		}
	}
}
ll LCA(ll x,ll y){
	if(depth[x] > depth[y]){
		swap(x,y);
	}
	ll diff = depth[y] - depth[x];
	REP(i,0,60){
		if((diff >> i) & 1){
			y = lca[i][y];
		}
		if(diff == 0) break;
	}
	REPI(i,0,20){
		if(lca[i][x] != lca[i][y]){
			x = lca[i][x];
			y = lca[i][y];
		}
		if(x == y){
			break;
		}
	}
	if(x != y){
		x = lca[0][x];
		y = lca[0][y];
	}
	return x;
}

int main()
{
	i_os;
	ll n,m;
	cin>>n>>m;
	ll arr[n+1];
	set<ll> s;
	REP(i,1,n+1){
		cin>>arr[i];
		s.insert(arr[i]);
	}
	REP(i,0,maxn) roots[i] = nullptr;

	// index compression
	map<ll,ll> mp;
	for(auto it:s){
		mp[it] = maxi;
		maxi++;
	}
	REP(i,1,n+1){
		values[mp[arr[i]]] = arr[i];
		arr[i] = mp[arr[i]];
	}

	// tree
	vector<ll> edges[n+1];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	// persistent seg tree
	ll start = 0,end = maxi;
    roots[0] = build(start,end);

	// lca
	initialize(edges,n,arr);

    while(m--){
    	ll i,j,k;
    	cin>>i>>j>>k;
    	ll c = LCA(i,j);
    	ll p = find_kth(roots[i],roots[j],roots[c],roots[parent[c]],0,maxi,k);
    	cout<<values[p]<<endl;
    }
	return 0;
}
