// https://www.spoj.com/problems/MKTHNUM/
// This time we have to answer queries of the form "What is the k-th smallest element in the range a[l…r]. 
// This query can be answered using a binary search and a Merge Sort Tree, but the time complexity for a single query would be O(log3n). 
// We will accomplish the same task using a persistent Segment Tree in O(logn).

ll const maxn = 100005;
ll values[maxn];

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

ll find_kth(Vertex* vl,Vertex *vr,ll start,ll end,ll k){
    if(start == end){
        return start;
    }
    ll mid = (start + end)/2, left_count = vr->l->sum - vl->l->sum;
    if(left_count >= k){
        return find_kth(vl->l, vr->l, start, mid, k);
    }
    return find_kth(vl->r, vr->r, mid+1, end, k-left_count);
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
    
    // index compression
    map<ll,ll> mp;
    ll curr = 0;
    for(auto it:s){
        mp[it] = curr;
        curr++;
    }
    REP(i,0,n){
        values[mp[arr[i]]] = arr[i];
        arr[i] = mp[arr[i]];
    }

    // find the 5th smallest number from the subarray [a[2], a[3], ..., a[19]]
    // find_kth(roots[2],roots[20],start,end,5);
    ll start = 0,end = curr;
    vector<Vertex*> roots;
    roots.push_back(build(start,end));
    REP(i,0,n){
        roots.push_back(update(roots.back(),start,end,arr[i]));
    }
    while(m--){
        ll i,j,k;
        cin>>i>>j>>k;
        ll p = find_kth(roots[i-1],roots[j],0,curr,k);
        cout<<values[p]<<endl;
    }
    return 0;
}