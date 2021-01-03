// This time we have to answer queries of the form "What is the k-th smallest element in the range a[l…r]. 
// This query can be answered using a binary search and a Merge Sort Tree, but the time complexity for a single query would be O(log3n). 
// We will accomplish the same task using a persistent Segment Tree in O(logn).

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
    ll mid = (left + right)/2;
    if(pos <= mid){
        return new Vertex(update(v->l, left, mid, pos), v->r);
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

void solve()
{
    ll start = 0,end = MAX_VALUE + 1;
    vector<Vertex*> roots;
    roots.push_back(build(start,end));
    REP(i,0,a.size()){
        roots.push_back(update(roots.back(),start,end,a[i]));
    }
    // find the 5th smallest number from the subarray [a[2], a[3], ..., a[19]]
    ll result = find_kth(roots[2],roots[20],start,end,5);
}