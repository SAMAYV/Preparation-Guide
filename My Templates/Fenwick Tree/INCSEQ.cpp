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

int mod = 5*pow(10,6);

void update(int** BIT,int index,ll value,int row){
    for(int i=index;i<=100001;i+=(i&(-i))){
        BIT[row][i] = (BIT[row][i] + value) % mod;
    }
}
ll query(int** BIT,int index,int row){
    ll count = 0;
    for(int i=index;i>0;i-=(i&(-i))){
        count = (count + BIT[row][i]) % mod;
    }
    return count;
}
int main()
{
    int n,k;
    cin>>n>>k;
    int** BIT = new int*[k+1];
    for(int i=0;i<k+1;i++)
        BIT[i] = new int[100002]();
    
    int* a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    
    update(BIT,a[0]+1,1,1);
    
    int max = a[0];
    for(int c=1;c<n;c++){
        
        if(a[c]>max)
            max = a[c];
        
        update(BIT,a[c]+1,1,1);
        
        for(int r=2;r<=k;r++){
            ll q = query(BIT,a[c],r-1);
            update(BIT,a[c]+1,q,r);
        }
        
    }
    cout<<query(BIT,max+1,k)<<" ";
    return 0;
}


