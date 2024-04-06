#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> lis(vector<int>& a){
    int n = a.size();
    vector<int> d(n+1,1e9);
    vector<int> index(n+1,-1);
    vector<int> parent(n+1,-1);
    d[0] = -1e9;

    for(int i = 0; i < n; i++){
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if(d[j-1] < a[i] && a[i] < d[j]){
            index[j] = i;
            d[j] = a[i];
            parent[i] = index[j-1];
        }
    }

    int len = 0;
    for(int i = 0; i <= n; i++){
        if(d[i] < 1e9)
            len = i;
    }
    vector<int> ans;
    int curr = index[len];
    while(curr != -1){
    	ans.push_back(a[curr]);
    	curr = parent[curr];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
// d[i] will be the element at which a subsequence of length i terminates. 
// If there are multiple such sequences, then we take the one that ends in the smallest element.
// parent[i] will be the index of the previous element for the optimal subsequence ending in element i.
