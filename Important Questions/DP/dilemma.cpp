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

Abhishek, a blind man recently bought N binary strings all of equal length .A binary string only contains '0's and '1's . The strings are numbered from 1 to N and all are distinct, but Abhishek can only differentiate between these strings by touching them. In one touch Abhishek can identify one character at a position of a string from the set. Find the minimum number of touches T Abhishek has to make so that he learn that all strings are different .
Constraints :
2<=N<=10
1<=|L|<=100 , L is length of the strings .
Input Format:

Line 1 : An Integer N, denoting the number of binary strings .
Next N lines : strings of equal length

Output Format:

Return the minimum number of touches

Sample Input :

2
111010
100100

Sample Output :

2

*/

int DP(int n, vector<string> v){
    int s = v[0].size();
    long** dp = new long*[s + 1];
    for(int i=0;i<s+1;i++){
        dp[i] = new long[1<<n];
        for(int j=0;j<(1<<n);j++)
            dp[i][j] = 100000;
    }
    for(int c=(1<<n)-1; c>=0; c--){
        if((c&(c-1))==0)
            dp[s][c] = 0;
    }
    for(int r=s-1;r>=0;r--){
        for(int c=(1<<n)-1;c>=0;c--){
            int mask = c;
            int mask1 = 0;
            int mask2 = 0;
            long count = 0;
            for(int i=0;i<v.size();i++){
                if(mask&(1<<i)){
                    count++;
                    if(v[i][r]=='1')
                        mask1 |=(1<<i);
                    else
                        mask2 |=(1<<i);
                }
            }
            dp[r][c] = min(dp[r+1][c],dp[r+1][mask1] + dp[r+1][mask2] + count);
        }
    }
    return dp[0][(1<<n)-1];
}
int dp[105][1<<12];

int findTouches(int pos, int mask, vector<string> &v){
    if(!(mask & (mask-1)) && mask) 
        return 0;

    if(pos == -1) 
        return 100000;

    if(mask == 0)
        return 0;
    
    if(dp[pos][mask]) 
        return dp[pos][mask];

    int newMask1 = 0, newMask2 = 0, touches = 0;
    for(int i = 0; i < v.size(); i++){
        if((mask>>i)&1){
            touches++;
            if(v[i][pos] == '0') newMask1 |= (1<<i);
            else newMask2 |= (1<<i);
        }
    }

    return dp[pos][mask] = min(findTouches(pos-1, newMask1, v)+findTouches(pos-1, newMask2, v)+touches, findTouches(pos-1, mask, v));
}

int minimumTouchesRequired(int n, vector<string> v){
    return findTouches(v[0].size()-1, (1<<n)-1, v);
    // return DP(n,v);
}
int main()
{
    
    return 0;
}