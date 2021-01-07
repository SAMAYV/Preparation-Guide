// https://codeforces.com/blog/entry/2034
// https://www.spoj.com/problems/MATGAME/

int main()
{
    i_os;
    ll t;
    cin>>t;
    while(t--){
    	ll n,m;
    	cin>>n>>m;
    	ll arr[n][m];
    	ll ans = 0;
    	REP(i,0,n){
    		REP(j,0,m){
    			cin>>arr[i][j];
    		}
    		ll curr = arr[i][m-1];
    		REPI(j,0,m-1){
    			if(arr[i][j] <= curr) curr = arr[i][j] - 1;
    			else curr = arr[i][j];
    		}
    		ans ^= curr;
    	}
    	if(ans) cout<<"FIRST\n";
    	else cout<<"SECOND\n";
    }
    return 0;
}
// Let grundy of i,j+1 element is grundy[rightmost element] = 3
// Then for current element (i,j), where grundy[x] denotes no of stones in current pile,
// grundy[0] = grundy[rightmost element](as it can move to rightmost element only)
// grundy[1] = mex{grundy[0]} = 0, grundy[2] = mex{grundy[1],grundy[0]} = mex{0,3} = 1...
// grundy[4] = mex{grundy[0]...grundy[3]} = mex{3,0,1,2} = 4
