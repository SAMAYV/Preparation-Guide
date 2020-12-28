ll zero_matrix(vector<vector<ll>>& a){
    ll n = a.size();
    ll m = a[0].size();

    ll ans = 0;
    vector<ll> d(m,-1), d1(m), d2(m);
    stack<ll> st;
    REP(i,0,n){
        REP(j,0,m){
            if(a[i][j] == 1){
                d[j] = i;
            }
        }
        REP(j,0,m){
            while(st.size() && d[st.top()] <= d[j]){
                st.pop();
            }
            d1[j] = st.empty() ? -1 : st.top();
            st.push(j);
        }
        while(st.size()){
            st.pop();
        }
        REPI(j,0,m){
            while(st.size() && d[st.top()] <= d[j]){
                st.pop();
            }
            d2[j] = st.empty() ? m : st.top();
            st.push(j);
        }
        while(st.size()){
            st.pop();
        }
        REP(j,0,m){
            ans = max(ans, (i - d[j])*(d2[j] - d1[j] - 1));
        }
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
    