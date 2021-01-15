// when there is only a query asking for sums, and modification queries of single elements.

struct Vertex {
    Vertex *l, *r;
    ll sum;
    Vertex(ll val) : l(nullptr), r(nullptr), sum(val){}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0){
        if(l) sum += l->sum;
        if(r) sum += r->sum;
    }
};

Vertex* build(ll* arr,ll start,ll end){
    if(start == end){
        return new Vertex(arr[start]);
    }
    ll mid = (start + end)/2;
    return new Vertex(build(arr,start,mid), build(arr,mid+1,end));
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

// for a modification query O(logn) new vertices will be created at max
Vertex* update(Vertex* v,ll start,ll end,ll pos,ll new_val){
    if(start == end){
        return new Vertex(new_val);
    }
    ll mid = (start + end)/2;
    if(pos <= mid){
        return new Vertex(update(v->l, start, mid, pos, new_val), v->r);
    }
    else {
        return new Vertex(v->l, update(v->r, mid+1, end, pos, new_val));
    }
}