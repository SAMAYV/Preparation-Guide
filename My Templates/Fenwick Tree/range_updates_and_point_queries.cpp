void add(ll idx,ll val,ll* tree,ll n){
    for(++idx; idx <= n; idx += (idx & -idx)){
        tree[idx] += val;
    }
}

// l and r are 0-based indices of array
void range_add(ll l,ll r,ll val,ll* tree){
    add(l,val,tree);
    add(r+1,-val,tree);
}

// idx is index of 0-based array
ll point_query(ll idx,ll* tree){
    ll ret = 0;
    for(++idx; idx > 0; idx -= (idx & -idx)){
        ret += tree[idx];
    }
    return ret;
}

int main()
{
	ll tree[n+1];
	return 0;
}
