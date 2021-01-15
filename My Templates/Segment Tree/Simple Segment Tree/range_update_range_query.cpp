// Now the modification query is to add a number to all elements in a range, and the reading query is to find the maximum in a range.

ll const maxn = 1e5 + 5;
ll tree[4*maxn];
ll lazy[4*maxn];

void push(ll v){
    tree[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    tree[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void buildtree(ll start,ll end,ll treenode,ll* arr){
    if(start == end){
        tree[treenode] = arr[start];
        lazy[treenode] = 0;
        return;
    }
    ll mid = (start+end)/2;
    buildtree(tree,start,mid,2*treenode,arr);
    buildtree(tree,mid+1,end,2*treenode+1,arr);
    tree[treenode] = max(tree[2*treenode],tree[2*treenode + 1]);
    lazy[treenode] = 0;
}

void update(ll treenode,ll start,ll end,ll left,ll right,ll addend){
    if(right < start || end < left){
        return;
    }
    if(left <= start && right >= end){
        tree[treenode] += addend;
        lazy[treenode] += addend;
        return;
    }
	push(treenode);
	ll mid = (start + end)/2;
	update(2*treenode, start, mid, left, right, addend);
    update(2*treenode+1, mid+1, end, left, right, addend);
    tree[treenode] = max(tree[treenode*2], tree[treenode*2+1]);
}

ll query(ll treenode,ll start,ll end,ll left,ll right){
    if(right < start || end < left){
        return -INF;
    }
    if(left <= start && right >= end){
        return tree[treenode];
    }
    push(v);
    ll mid = (start + end)/2;
    return max(query(treenode*2, start, mid, left, right), query(treenode*2+1, mid+1, end, left, right));
}