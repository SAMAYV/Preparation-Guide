// Find the smallest number greater or equal to a specified number. With modification queries.

// construction time of O(nlognlogn)
void build(multiset<ll>* tree,ll* arr,ll start,ll end,ll treenode){
    if(start == end){
        tree[treenode] = multiset<ll>(1,arr[start]);
    } 
    else { 
        ll mid = (start + end)/2;
        build(tree,arr,start,mid,2*treenode);
        build(tree,arr,mid + 1,end,2*treenode + 1);
        merge(tree[2*treenode].begin(), tree[2*treenode].end(), tree[2*treenode+1].begin(), tree[2*treenode+1].end(), 
            inserter(tree[treenode],tree[treenode].begin()));
    }
}

// The answer to the query in one segment of the tree takes O(logn) time, and the entire query is processed in O(lognlogn).
ll query(multiset<ll>* tree,ll start,ll end,ll left,ll right,ll treenode,ll x){
    if(start > right || end < left){
        return INF;
    }
    if(left <= start && end >= right){
        auto pos = tree[treenode].lower_bound(x);
        if(*pos >= x){
            return *pos;
        }
        return INF;
    }
    ll mid = (start + end)/2;
    return min(query(tree,start,mid,left,right,x,2*treenode), query(tree,mid+1,end,left,right,x,2*treenode+1));
}

// Processing of this modification query also takes O(lognlogn) time.
void update(multiset<ll>* tree,ll* arr,ll start,ll end,ll treenode,ll pos,ll new_val){
    tree[treenode].erase(tree[treenode].find(arr[pos]));
    tree[treenode].insert(new_val);
    if(start != end){
        ll mid = (start + end)/2;
        if(pos <= mid){
            update(tree,arr,start,mid,2*treenode,pos,new_val);
        }
        else {
            update(tree,arr,mid+1,end,2*treenode,pos,new_val);
        }
    } 
    else {
        arr[pos] = new_val;
    }
}

// Pending: Find the smallest number greater or equal to a specified number. Acceleration with "fractional cascading".