int main()
{
    ll n,k,p;
    cin>>n>>k>>p;
    ll arr[n];
    REP(i,0,n){
        cin>>arr[i];
    }
    ll l = 1,u = 1e10;
    ll ans = 0;
    while(l <= u){
        ll mid = (l + u)/2;
        ll temp[n];
        REP(i,0,n){
            temp[i] = max(0LL,mid - arr[i]);
        }
        ll i = 0, ct = 0, prev = 0, temp_ans = 0, temp1 = 0;
        while(i < n){
            if(temp[i] > prev){
                temp_ans += temp[i] - temp1;
                temp1 = temp[i] - temp1;
                ct = 0;
                prev = temp[i];
            }
            if(prev > 0){
                ct++;
            }
            if(ct >= k){
                ct = 0;
                prev = 0;
                temp1 = 0;
            }
            i++;
        }
        if(temp_ans <= p){
            ans = max(ans,mid);
            l = mid + 1;
        }
        else {
            u = mid - 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}