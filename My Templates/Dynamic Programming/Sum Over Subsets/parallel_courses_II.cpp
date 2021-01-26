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
