// Find the smallest number greater or equal to a specified number. No modification queries.
// We want to answer queries of the following form: for three given numbers (l,r,x) we have to find 
// the minimal number in the segment a[l…r] which is greater than or equal to x.

// Because this structure of the Segment Tree and the similarities to the merge sort algorithm, 
// the data structure is also often called "Merge Sort Tree".
// O(nlogn) memory
// O(nlogn) time

void build(vector<ll>* tree,ll* arr,ll start,ll end,ll treenode){
    if(start == end){
        tree[treenode] = vector<ll>(1,arr[start]);
    } 
    else { 
        ll mid = (start + end)/2;
        build(tree,arr,start,mid,2*treenode);
        build(tree,arr,mid + 1,end,2*treenode + 1);
        merge(tree[2*treenode].begin(), tree[2*treenode].end(), tree[2*treenode+1].begin(), tree[2*treenode+1].end(), 
        	back_inserter(tree[treenode]));
    }
}

// The answer to the query in one segment of the tree takes O(logn) time, and the entire query is processed in O(lognlogn).
ll query(vector<ll>* tree,ll start,ll end,ll left,ll right,ll treenode,ll x){
    if(start > right || end < left){
        return INF;
    }
    if(left <= start && end >= right){
        vector<ll>::iterator pos = lower_bound(tree[treenode].begin(),tree[treenode].end(),x);
        if(pos != t[v].end()){
            return *pos;
        }
        return INF;
    }
    ll mid = (start + end)/2;
    return min(query(tree,start,mid,left,right,x,2*treenode), query(tree,mid+1,end,left,right,x,2*treenode+1));
}
