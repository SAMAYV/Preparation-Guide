// https://www.codechef.com/problems/CHEFAOR

vector<vector<ll>> dp,C,state;

void solve(ll n,ll m,ll arr[]){
    dp.clear();
    dp.resize(m+5,vector<ll>(n+5,0));
    state.clear();
    state.resize(m+5,vector<ll>(n+5,0));
    C.clear();
    C.resize(n+5,vector<ll>(n+5,0));
    
    REP(i,1,n+1){
        REP(j,i,n+1){
            C[i][j] = arr[j-1];
            if(i <= j-1) C[i][j] |= C[i][j-1];
        }
    }
   	REP(i,0,n+1){
   		state[0][i] = 0;
   	}
   	REP(i,0,m+1){
   		state[i][n+1] = n-1;
   	}

    REP(i,1,m+1){
    	REPI(j,1,n+1){
    		REP(k,state[i-1][j],state[i][j+1]+1){
    			if(dp[i-1][k] + C[k+1][j] > dp[i][j]){
    				dp[i][j] = dp[i-1][k] + C[k+1][j];
    				state[i][j] = k;
    			}
    		}
    	}
    }
    cout<<dp[m][n]<<endl;
}

int main()
{
	i_os;
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
