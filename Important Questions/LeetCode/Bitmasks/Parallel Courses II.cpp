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
typedef tree<string,null_type,less<string>,rb_tree_tag,tree_order_statistics_node_update> indexed_set2;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

// https://leetcode.com/contest/biweekly-contest-29/problems/parallel-courses-ii/

/*
Given the integer n representing the number of courses at some university labeled from 1 to n, and the array dependencies where dependencies[i] = [xi, yi]  represents a prerequisite relationship, that is, the course xi must be taken before the course yi.  Also, you are given the integer k.

In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.

Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.


    1 <= n <= 15
    1 <= k <= n
    0 <= dependencies.length <= n * (n-1) / 2
    dependencies[i].length == 2
    1 <= xi, yi <= n
    xi != yi
    All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
    The given graph is a directed acyclic graph.

*/

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        // dependency[i]: dependency mask of course i, the set bits is dependent
        vector<int> dependency(n, 0);
        for (size_t i = 0; i < dependencies.size(); ++i) {
            int course = dependencies[i][1] - 1;
            int prerequisite = dependencies[i][0] - 1;
            dependency[course] |= 1 << prerequisite;
        }

        // prerequisites[i]: prerequisites mask of mask i, the set bits is prerequisites
        vector<int> prerequisites(1 << n, 0);
        // iterate all mask and generate prerequisites mask of each mask
        for (int i = 0; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    prerequisites[i] |= dependency[j];
                }
            }
        }

        // dp[i]: minimum number of semesters of mask i, the set bits are courses that have not been taken
        vector<int> dp(1 << n, n + 1);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) {
            // iterate all submask of mask i, and this mask is the mask of last semester
            // see: https://cp-algorithms.com/algebra/all-submasks.html
            for (int j = i; j; j = (j - 1) & i) {
                if (count_setbit(j) > k) {
                    continue;
                }

                int already_taken = i ^ ((1 << n) - 1);
                if ((already_taken & prerequisites[j]) == prerequisites[j]) {
                    dp[i] = min(dp[i], dp[i ^ j] + 1);
                }
            }
        }

        return dp[(1 << n) - 1];
    }

private:
    int count_setbit(int mask) {
        if (mask == 0) {
            return 0;
        }
        return 1 + count_setbit(mask & (mask - 1));
    }
};

int main()
{
	
	return 0;
}
