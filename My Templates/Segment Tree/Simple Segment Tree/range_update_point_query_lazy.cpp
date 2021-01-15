// Suppose now that the modification query asks to assign each element of a certain segment a[l…r] to some value p. 
// As a second query we will again consider reading the value of the array a[i].

ll const maxn = 1e5 + 5;
ll marked[4*maxn];

void push(ll* tree,ll treenode){
    if(marked[treenode]){
        tree[treenode*2] = tree[treenode*2+1] = tree[treenode];
        marked[treenode*2] = marked[treenode*2+1] = 1;
        marked[treenode] = 0;
    }
}

void buildtree(ll* tree,ll start,ll end,ll treenode,ll* arr){
    if(start == end){
        tree[treenode] = arr[start];
        marked[treenode] = 0;
        return;
    }
    ll mid = (start+end)/2;
    buildtree(tree,start,mid,2*treenode,arr);
    buildtree(tree,mid+1,end,2*treenode+1,arr);
    tree[treenode] = 0;
    marked[treenode] = 0;
}

ll query(ll* tree,ll start,ll end,ll treenode,ll ind){
    if(start == end){
        return tree[treenode];
    }
    push(tree,treenode);
    ll mid = (start + end)/2;
    if(ind <= mid){
        return query(tree,start,mid,2*treenode,ind);
    }
    else {
        return query(tree,mid+1,end,2*treenode+1,ind);
    }    
}

// left to right which is required range
void update(ll* tree,ll start,ll end,ll left,ll right,ll treenode,ll val){
    if(right < start || end < left){
        return;
    }
    if(left <= start && right >= end){
        tree[treenode] = val;
        marked[treenode] = 1;
        return;
    }
    push(tree,treenode);
    ll mid = (start + end)/2;
    update(tree,start,mid,left,right,2*treenode,val);
    update(tree,mid+1,end,left,right,2*treenode+1,val);
}