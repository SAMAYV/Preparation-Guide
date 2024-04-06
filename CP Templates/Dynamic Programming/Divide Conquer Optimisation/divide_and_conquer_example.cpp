// https://www.codechef.com/problems/CHEFAOR

vector<vector<ll>> dp,C,state;

// This can be done by the following pseudocode which for fixed i applies divide and conquer on j  
// and keeps range (jleft,jright) of values of j for which we are seeking the answer and the 
// corresponding range (kleft,kright) of the possible values for optimal k when j is in the range (jleft,jright)
void compute(ll i,ll jleft,ll jright,ll kleft,ll kright)
{
    if(jleft > jright){
        return;    
    } 
    ll jmid = (jleft + jright) / 2;
    ll bestk = 0; 

    // calculating the answer for jmid and state[i][jmid] <= state[i][j] for all j >= jmid due to monotonicity
    REP(k,kleft,jmid){
        if(dp[i - 1][k] + C[k + 1][jmid] > dp[i][jmid]){
            dp[i][jmid] = dp[i - 1][k] + C[k + 1][jmid]; 
            bestk = k;
            state[i][jmid] = k;
        } 
    } 
    // Divide and conquer 
    compute(i, jleft, jmid - 1, kleft, bestk);
    compute(i, jmid + 1, jright, bestk, kright); 
}

void solve(ll n,ll m,ll arr[]){
    dp.clear();
    dp.resize(m+1,vector<ll>(n+1,0));
    state.clear();
    state.resize(m+1,vector<ll>(n+1,0));
    C.clear();
    C.resize(n+1,vector<ll>(n+1,0));
    
    // compute C
    REP(i,1,n+1){
        REP(j,i,n+1){
            C[i][j] = arr[j-1];
            if(i <= j-1) C[i][j] |= C[i][j-1];
        }
    }
    // calculate for i = 0
    REP(i,1,m+1){
        compute(i,0,n,0,n);
    }
    cout<<dp[m][n]<<endl;
}

int main()
{
    ll t;
    cin>>t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        ll arr[n];
        REP(i,0,n){
            cin>>arr[i];
        }
        solve(n,k,arr);
    }
    return 0;
}