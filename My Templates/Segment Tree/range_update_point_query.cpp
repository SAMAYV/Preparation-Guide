// The modification query should add a number x to all numbers in the segment a[l…r]. 
// The second query, that we are supposed to answer, asked simply for the value of a[i].

void buildtree(ll* tree,ll start,ll end,ll treenode,ll* arr){
    if(start == end){
        tree[treenode] = arr[start];
        return;
    }
    ll mid = (start+end)/2;
    buildtree(tree,start,mid,2*treenode,arr);
    buildtree(tree,mid+1,end,2*treenode+1,arr);
    tree[treenode] = 0;
}

ll query(ll* tree,ll start,ll end,ll treenode,ll ind){
    if(start == end){
        return tree[treenode];
    }
    ll mid = (start + end)/2;
    if(ind <= mid){
        return tree[treenode] + query(tree,start,mid,2*treenode,ind);
    }
    else {
        return tree[treenode] + query(tree,mid+1,end,2*treenode+1,ind);
    }    
}

// left to right which is required range
void update(ll* tree,ll start,ll end,ll left,ll right,ll treenode,ll val){
    if(right < start || end < left){
        return;
    }
    if(left <= start && right >= end){
        tree[treenode] += val;
        return;
    }
    ll mid = (start + end)/2;
    update(tree,start,mid,left,right,2*treenode,val);
    update(tree,mid+1,end,left,right,2*treenode+1,val);
}