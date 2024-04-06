/*
Given a sequence A1 , A2 , A3 .. AN of length N . Find total number of wave subsequences having length greater than 1.
Wave subsequence of sequence A1 , A2 , A3 .. AN is defined as a set of integers i1 , i2 .. ik such that Ai1 < Ai2 > Ai3 < Ai4 .... 
or Ai1 > Ai2 < Ai3 > Ai4 .... and i1 < i2 < ...< ik.Two subsequences i1 , i2 .. ik and j1 , j2 .. jm are considered different 
if k != m or there exists some index l such that il ! = jl

INPUT
First line of input consists of integer N denoting total length of sequence.Next line consists of N integers A1 , A2 , A3 .. AN .

OUTPUT
Output total number of wave subsequences of given sequence . Since answer can be large, output it modulo 10^9+7

CONSTRAINTS
1 ≤ N ≤ 10^5
1 ≤ Ai ≤ 10^5

SAMPLE INPUT
5
1 3 5 4 2

SAMPLE OUTPUT
17

Explanation
All the possible sequences are: [ 1 3 ] , [1 5 ] , [ 1 4 ] , [1 2 ] , [1 3 2] , [1 4 2 ] , [1 5 2] , [1 5 4] , [3 5] , [3 4] , [3 2] , 
[3 5 2] , [3 4 2] , [3 5 4] , [5 4] , [5 2 ] , [4 2] . Note that value in the bracket are the values from the original sequence whose 
positions are maintained.
*/

int mod = 1e9 + 7;

void update(ll index,ll value,vector<vector<ll>>& tree,ll row){
    for(ll i = index; i <= 100000; i += (i & (-i))){
        tree[row][i] = (tree[row][i] + value) % mod;
    }
}
ll query(ll row,ll index,vector<vector<ll>>& tree){
    ll count = 0;
    for(ll i = index; i > 0; i -= (i & (-i))){
        count = (count + tree[row][i]) % mod;
    }
    return count;
}
int main() 
{
	ll n;
    cin>>n;
    ll arr[n];
    REP(i,0,n){
        cin>>arr[i];
    }
    vector<vector<ll>> tree(3,vector<ll>(100001,0));
    ll maxval = arr[0];
    update(arr[0],1,tree,2);
    ll sum = 0;
    REP(i,1,n){
        ll a = (query(0,arr[i]-1,tree) + query(2,arr[i]-1,tree)) % mod;
        ll b = (query(1,maxval,tree) - query(1,arr[i],tree) + query(2,maxval,tree) - query(2,arr[i],tree) + mod) % mod;
        sum = (sum + a + b) % mod;
        update(arr[i],a,tree,1);
        update(arr[i],b,tree,0);
        update(arr[i],1,tree,2);            
        maxval = max(maxval,arr[i]);
    }
    cout<<sum<<endl;
}


