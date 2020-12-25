#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long 
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set1;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

/*

Given a sequence A1 , A2 , A3 .. AN of length N . Find total number of wave subsequences having length greater than 1.
Wave subsequence of sequence A1 , A2 , A3 .. AN is defined as a set of integers i1 , i2 .. ik such that Ai1 < Ai2 > Ai3 < Ai4 .... or Ai1 > Ai2 < Ai3 > Ai4 .... and i1 < i2 < ...< ik.Two subsequences i1 , i2 .. ik and j1 , j2 .. jm are considered different if k != m or there exists some index l such that il ! = jl
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

All the possible sequences are: [ 1 3 ] , [1 5 ] , [ 1 4 ] , [1 2 ] , [1 3 2] , [1 4 2 ] , [1 5 2] , [1 5 4] , [3 5] , [3 4] , [3 2] , [3 5 2] , [3 4 2] , [3 5 4] , [5 4] , [5 2 ] , [4 2] . Note that value in the bracket are the values from the original sequence whose positions are maintained.

*/

int mod = pow(10,9) + 7;

void update(int index,int value,int** BIT,int row){
    for(int i=index;i<=100000;i+=(i&(-i))){
        BIT[row][i] = (BIT[row][i] + value) % mod;
    }
}
long long query(int row,int index,int** BIT){
    long long count = 0;
    for(int i=index;i>0;i-=(i&(-i))){
        count = (count + BIT[row][i]) % mod;
    }
    return count;
}
int main() {

	int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    int** BIT = new int*[3];
    for(int i=0;i<3;i++)
        BIT[i] = new int[100001]();
    
    int maxval = arr[0];
    update(arr[0],1,BIT,2);
    long long sum = 0;
    for(int i=1;i<n;i++){
        long long a = (query(0,arr[i]-1,BIT) + query(2,arr[i]-1,BIT)) % mod;
        long long b = (query(1,maxval,BIT) - query(1,arr[i],BIT) + query(2,maxval,BIT) - query(2,arr[i],BIT) + mod) % mod;
        sum = (sum + a + b) % mod;
        update(arr[i],a,BIT,1);
        update(arr[i],b,BIT,0);
        update(arr[i],1,BIT,2);
        if(maxval<arr[i])
            maxval = arr[i];
    }
    cout<<sum<<endl;
}


