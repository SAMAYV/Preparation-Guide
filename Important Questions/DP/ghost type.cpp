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
#define MAX 1e6
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

/*

Gengar has got an integer N. Now using his ghostly powers, he can create the permutation from 1 to N of this given number.
Since, he's a special kind of Poke'mon, so he thinks he deserves special permutations. He wants to find the total number of special permutations of length N, consisting of the integers from 1 to N

.
A permutation is called special if it satisfies following condition:

If Ap & Aq == Ap, then p < q, where p and q are two distinct indices of permutation and A is the permutation itself. "&" denotes the bitwise and operation.

Help Gengar in finding the number of such permutations.
Input format:

The only line of input will consist of a single integer N denoting the length of the permutation.

Output format:

Output the total number of special permutations of length N

.
Constraints:

1 ≤ N ≤ 20
SAMPLE INPUT

4
SAMPLE OUTPUT

8
Explanation

All the special permutations of length 4 are: 1 2 3 4

1 2 4 3

1 4 2 3

2 1 3 4

2 1 4 3

2 4 1 3

4 1 2 3

4 2 1 3

*/

long long perm(int n){
    long long* dp = new long long[1<<n];
    for(int i=0;i<(1<<n);i++)
        dp[i] = 0;
    dp[0] = 1;
    
    for(int i=0;i<(1<<n)-1;i++){
        for(int j=0;j<n;j++){
            if(!((1<<j)&i))
            {
                int val = j+1;
                int f = 0;
                for(int k=1;k<=n;k++){
                    if(((val & k) == val)){
                        if(((1<<(k-1))&i)){
                            f = 1;
                            break;    
                        }
                    }
                }
                if(f!=1)
                    dp[i|(1<<j)] += dp[i];
            }
        }
    }
    return dp[(1<<n)-1];
}
int main()
{
    int n;
    cin>>n;
    cout<<perm(n);
    return 0;
}