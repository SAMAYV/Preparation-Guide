vector<ll> lis(vector<ll>& arr){
    ll n = arr.size();
    vector<ll> d(n+1,1e9);
    vector<ll> index(n+1,-1);
    vector<ll> parent(n+1,-1);
    d[0] = -1e9;

    REP(i,0,n){
        ll j = upper_bound(d.begin(), d.end(), arr[i]) - d.begin();
        if(d[j-1] < a[i] && a[i] < d[j]){
            index[j] = i;
            d[j] = a[i];
            parent[i] = index[j-1];
        }
    }

    ll len = 0;
    REP(i,0,n+1){
        if(d[i] < 1e9)
            len = i;
    }
    vector<ll> ans;
    ll curr = index[len];
    while(curr != -1){
    	ans.push_back(arr[curr]);
    	curr = parent[curr];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
// d[i] will be the element at which a subsequence of length i terminates. 
// If there are multiple such sequences, then we take the one that ends in the smallest element.
// parent[i] will be the index of the previous element for the optimal subsequence ending in element i.

int main()
{
	return 0;
}