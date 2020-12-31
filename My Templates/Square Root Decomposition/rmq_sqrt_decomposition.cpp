void RMQ(ll n,ll arr[],vector<pair<ll,ll>> queries){
    ll len = sqrtl(n) + 1; 
    vector<ll> b(len);
    REP(i,0,n){
        b[i/len] += arr[i];
    }

    // answering the queries
    REP(i,0,queries.size()){
        ll l = queries[i].first, r = queries[i].second;
        ll sum = 0;
        
        // First Method
        for(ll i=l;i<=r;){
            if(i % len == 0 && i + len - 1 <= r){
                // if the whole block starting at i belongs to [l, r]
                sum += b[i / len];
                i += len;
            }
            else {
                sum += arr[i];
                ++i;
            }
        }

        // Second Method
        ll c_l = l/len, c_r = r/len;
        if(c_l == c_r){
            REP(i,l,r+1){
                sum += arr[i];
            }
        }
        else {
            for(ll i=l, end=(c_l+1)*len-1; i<=end; ++i){
                sum += arr[i];
            }
            for(ll i=c_l+1; i<=c_r-1; ++i){
                sum += b[i];
            }
            for(ll i=c_r*len; i<=r; ++i){
                sum += arr[i];
            }
        }
    }
}
int main()
{   
    
    return 0;
}   
    