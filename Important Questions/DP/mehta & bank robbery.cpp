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

One fine day, when everything was going good, Mehta was fired from his job and had to leave all the work. So, he decided to become a member of gangster squad and start his new career of robbing. Being a novice, mehta was asked to perform a robbery task in which he was given a bag having a capacity W units. So, when he reached the house to be robbed, there lay N items each having particular weight and particular profit associated with it. But, theres a twist associated, He has first 10 primes with him, which he can use atmost once, if he picks any item x, then he can multiply his profit[x] with any of the first 10 primes and then put that item into his bag. Each prime can only be used with one particular item and one item can only have atmost one prime multiplied with its profit. Its not necessary to pick all the items. If he doesnt want to use a prime with any particular item, he can simply add the profit as it is, more specifically, 1*profit[x] for xth item will get added to its total profit, and that he can do with as many items as he wants. He cannot fill his bag more than weight W units. Each item should be picked with its whole weight, i.e it cannot be broken into several other items of lesser weight. So, now to impress his squad, he wishes to maximize the total profit he can achieve by robbing this wealthy house.

Input:

First Line of input containts two integers N and W. Next N lines contain information of ith item, describing profit and weight of the ith item, profit and weight are separated by single space.

Output:

In a single line, output the maximum profit obtainable.

Constraints:

1 <= N <= 2000, 1 <= W <= 2000

1 <= Profit[i] <= 10^9, 1 <= Weight[i] <= 2000
SAMPLE INPUT

3 4

1 1

2 1

3 1
SAMPLE OUTPUT

152
Explanation:

As all, the items can be picked, so maximum profit is equal to = 1 X 19 + 2 X 23 + 3 X 29 = 152

*/

struct knap {
    ll value,weight;
};
bool compare(knap k1,knap k2){
    return k1.value < k2.value;
}
ll DP(knap* arr,int n,ll w,int prime[11]){
    ll*** dp = new ll**[2];
    dp[0] = new ll*[n+1];
    dp[1] = new ll*[n+1];
    for(int i=0;i<n+1;i++){
        dp[0][i] = new ll[w+1]();
        dp[1][i] = new ll[w+1]();
    }
    
    for(int r=1;r<n+1;r++){
        for(int c=1;c<w+1;c++){
            dp[0][r][c] = dp[0][r-1][c];
            if(c-arr[r-1].weight >=0)
                dp[0][r][c] = max(dp[0][r-1][c], dp[0][r-1][c-arr[r-1].weight] + arr[r-1].value);
        }
    }
    int k = 1;
    while(k<11)
    {
        int v = k%2;
        for(int r=1;r<n+1;r++){
            for(int c=1;c<w+1;c++){
                
                dp[v][r][c] = dp[v][r-1][c];
                
                if(c-arr[r-1].weight >=0)
                    dp[v][r][c] = max(dp[v][r-1][c] , max(dp[v][r-1][c-arr[r-1].weight] + arr[r-1].value , 
                                  dp[v ^ 1][r-1][c-arr[r-1].weight] + prime[k] * arr[r-1].value));    
            }
        }
        k++;
    }
    return dp[0][n][w];
}
int main()
{
    int n,w;
    cin>>n>>w;
    knap* arr = new knap[n];
    for(int i=0;i<n;i++){
        cin>>arr[i].value>>arr[i].weight;
    }
    sort(arr,arr+n,compare);
    int prime[11] = {1,2,3,5,7,11,13,17,19,23,29};
    cout<<DP(arr,n,w,prime);
    return 0;
}