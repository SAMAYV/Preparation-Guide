/*
Given a sequence of N (1 ≤ N ≤ 10,000) integers S1, ..., SN (0 ≤ Si < 100,000), compute the number of increasing subsequences of S with length K (1 ≤ K ≤ 50 and K ≤ N); that is, the number of K-tuples i1, ..., iK such that 1 ≤ i1 < ... < iK ≤ N and Si1 < ... < SiK.

Input
The first line contains the two integers N and K. The following N lines contain the integers of the sequence in order.

Output
Print a single integer representing the number of increasing subsequences of S of length K, modulo 5,000,000.

Sample Input
4 3
1
2
2
10

Output:
2
*/

int mod = 5000000;

void update(vector<vector<ll>>& tree,ll index,ll value,ll row){
    for(ll i = index; i <= 100001; i += (i & (-i))){
        tree[row][i] = (tree[row][i] + value) % mod;
    }
}
ll query(vector<vector<ll>>& tree,ll index,ll row){
    ll count = 0;
    for(ll i = index; i > 0; i -= (i & (-i))){
        count = (count + tree[row][i]) % mod;
    }
    return count;
}
int main()
{
    ll n,k;
    cin>>n>>k;
    vector<vector<ll>> tree(k+1,vector<ll>(100002,0));
    vector<ll> arr(n);
    REP(i,0,n){
        cin>>arr[i];
    }
    update(tree,arr[0]+1,1,1);
    ll maxi = arr[0];
    REP(c,1,n){
        maxi = max(maxi,arr[c])
        update(tree,arr[c] + 1,1,1);
        REP(r,2,k+1){
            ll q = query(tree,arr[c],r - 1);
            update(tree,arr[c] + 1,q,r);
        }
    }
    cout<<query(tree,maxi+1,k)<<" ";
    return 0;
}


