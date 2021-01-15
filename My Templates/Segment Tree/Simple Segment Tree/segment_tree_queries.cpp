// searching for kth zero in O(logn)
ll find_kth(ll* tree,ll start,ll end,ll k,ll treenode){
    if(k > tree[treenode]){
        return -1;
    }
    if(start == end){
        return start;
    }
    ll mid = (start + end)/2;
    if(tree[2*treenode] >= k){
        return find_kth(tree,start,mid,k,2*treenode);
    }
    else {
        return find_kth(tree,mid+1,end,k - tree[2*treenode],2*treenode + 1);
    }
}

// The task is as follows: for a given value x and a range a[l…r] find the smallest i in the range a[l…r], such that a[i] is greater than x.
ll get_first(ll* tree,ll start,ll end,ll left,ll right,ll treenode,ll x){
    if(start > right || end < left){
    	return -1;	
    } 
    if(left <= start && end <= right){
        if(tree[treenode] <= x){
        	return -1;
        } 
        while(start != end){
            ll mid = (start + end)/2;
            if(tree[2*treenode] > x){
                treenode = 2*treenode;
                end = mid;
            }
            else {
                treenode = 2*treenode + 1;
                start = mid + 1;
            }
        }
        return start;
    }
    ll mid = (start + end)/2;
    ll rs = get_first(tree,start,mid,left,right,2*treenode,x);
    if(rs != -1) return rs;
    return get_first(tree,mid+1,end,left,right,2*treenode + 1,x);
}
