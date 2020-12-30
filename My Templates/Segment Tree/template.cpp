void buildtree(ll* tree,ll start,ll end,ll treenode,ll* arr){
    if(start == end){
        tree[treenode] = arr[start];
        return;
    }
    ll mid = (start+end)/2;
    buildtree(tree,start,mid,2*treenode,arr);
    buildtree(tree,mid+1,end,2*treenode+1,arr);
    tree[treenode] = min(tree[2*treenode],tree[2*treenode+1]);
}
void update(ll* tree,ll start,ll end,ll treenode,ll ind,ll val){
    if(ind < start || ind > end){
        return;
    }
    if(start == end){
        tree[treenode] = val;
        return;
    }
    ll mid = (start + end)/2;
    update(tree,start,mid,2*treenode,ind,val);
    update(tree,mid+1,end,2*treenode+1,ind,val);
    tree[treenode] = min(tree[2*treenode],tree[2*treenode+1]);    
}

// left to right which is required range
ll query(ll* tree,ll start,ll end,ll left,ll right,ll treenode){
    if(right < start || end < left){
        return 1e9;
    }
    if(left <= start && right >= end){
        return tree[treenode];
    }
    ll mid = (start + end)/2;
    ll q1 = query(tree,start,mid,left,right,2*treenode);
    ll q2 = query(tree,mid+1,end,left,right,2*treenode+1);
    return min(q1,q2);    
}
