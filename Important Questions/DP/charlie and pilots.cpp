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

Charlie acquired airline transport company and to stay in business he needs to lower the expenses by any means possible. There are N pilots working for his company (N is even) and N/2 plane crews needs to be made. A plane crew consists of two pilots - a captain and his assistant. A captain must be older than his assistant. Each pilot has a contract granting him two possible salaries - one as a captain and the other as an assistant. A captain's salary is larger than assistant's for the same pilot. However, it is possible that an assistant has larger salary than his captain. Write a program that will compute the minimal amount of money Charlie needs to give for the pilots' salaries if he decides to spend some time to make the optimal (i.e. the cheapest) arrangement of pilots in crews.
Input

The first line of input contains integer N, 2 ≤ N ≤ 10,000, N is even, the number of pilots working for the Charlie's company. The next N lines of input contain pilots' salaries. The lines are sorted by pilot's age, the salaries of the youngest pilot are given the first. Each of those N lines contains two integers separated by a space character, X i Y, 1 ≤ Y < X ≤ 100,000, a salary as a captain (X) and a salary as an assistant (Y).

Output

The first and only line of output should contain the minimal amount of money Charlie needs to give for the pilots' salaries. 

Sample Input

4 
5000 3000 
6000 2000 
8000 1000 
9000 6000 

Sample Output

19000 

*/
int DP(int* cap,int* ast,int n){
    int** dp = new int*[n/2 + 1];
    for(int i=0;i<n/2 + 1;i++){
        dp[i] = new int[n];
    }
    for(int i=0;i<n;i++){
        dp[0][i] = 0;
    }
    dp[1][0] = ast[0];
    for(int i=2;i<=n/2;i++){
        dp[i][0] = 0;
    }
    
    for(int c=1;c<n;c++){
        for(int r=1;r<=n/2;r++){
            int captains = c+1-r;
            if(captains>r)
                dp[r][c] = 0;
            else {
                if(dp[r-1][c-1]!=0 && dp[r][c-1]!=0)
                    dp[r][c] = min(dp[r-1][c-1] + ast[c],dp[r][c-1] + cap[c]);
                else if(dp[r-1][c-1]!=0 && dp[r][c-1]==0)
                    dp[r][c] = dp[r-1][c-1] + ast[c];
                else if(dp[r-1][c-1]==0 && dp[r][c-1]!=0)
                    dp[r][c] = dp[r][c-1] + cap[c];
                else
                    dp[r][c] = 0;
            }
        }
    }
    return dp[n/2][n-1];
} 
int main()
{
    int n;
    cin>>n;
    int* cap = new int[n];
    int* ast = new int[n];
    for(int i=0;i<n;i++){
        cin>>cap[i]>>ast[i];
    }    
    cout<<DP(cap,ast,n);
    return 0;
}        
