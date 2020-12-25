#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

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
//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);

int zero_matrix(vector<vector<int>> a) {
    int n = a.size();
    int m = a[0].size();

    int ans = 0;
    vector<int> d(m, -1), d1(m), d2(m);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1)
                d[j] = i;
        }

        for (int j = 0; j < m; ++j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d1[j] = st.empty() ? -1 : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();

        for (int j = m - 1; j >= 0; --j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d2[j] = st.empty() ? m : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();

        for (int j = 0; j < m; ++j)
            ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1));
    }
    return ans;
}

/*

We can solve the problem in O(n*m*m) iterating through rows, considering every possible left and right columns for a submatrix. 
The bottom of the rectangle will be the current row, and using d[i][j] we can find the top row. However, it is possible to go further 
and significantly improve the complexity of the solution.

It is clear that the desired zero submatrix is bounded on all four sides by some ones, which prevent it from increasing in size and improving the answer. 
Therefore, we will not miss the answer if we act as follows: for every cell j in row i (the bottom row of a potential zero submatrix) we will have d[i][j] 
as the top row of the current zero submatrix. It now remains to determine the optimal left and right boundaries of the zero submatrix, 
i.e. maximally push this submatrix to the left and right of the j-th column.

What does it mean to push the maximum to the left? It means to find an index k1 for which d[i][k1] > d[i][j], and at the same time k1 - the closest one 
to the left of the index j. It is clear that then k1 + 1 gives the number of the left column of the required zero submatrix. 
If there is no such index at all, then put k1 = -1(this means that we were able to extend the current zero submatrix to the left all 
the way to the border of matrix a).

Symmetrically, you can define an index k2 for the right border: this is the closest index to the right of j such that d[i][k2] > d[i][j] 
(or m, if there is no such index).

So, the indices k1 and k2, if we learn to search for them effectively, will give us all the necessary information about the current zero submatrix. 
In particular, its area will be equal to (i - d[i][j]) * (k2 - k1 - 1).

*/

int main()
{   
    
    return 0;
}   
    