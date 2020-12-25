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

struct Query {
    ll L, R, idx;
};

struct subset {
	ll parent;
};

void initialise(subset* s,ll n){
	REP(i,0,n){
		s[i].parent = i;
	}
}

ll find(ll x,subset* s){
	if(s[x].parent == x)
		return x;
	s[x].parent = find(s[x].parent,s);
	return s[x].parent;
}

int main()
{
	// We are given an array a[] and we have to compute some minima in given segments of the array.
	// We will iterate over the array and when we are at the ith element we will answer all queries (L, R) with R == i. 
	// To do this efficiently we will keep a DSU using the first i elements with the following structure: 
	// the parent of an element is the next smaller element to the right of it. 
	// Then using this structure the answer to a query will be the a[find_set(L)], the smallest number to the right of L.
	// container[i] contains all queries with R == i.
	subset s[n];
	initialise(s,n);
	vector<ll> answer(q);

	stack<ll> st;
	REP(i,0,n){
    	while(st.size() && arr[st.top()] > arr[i]){
        	s[st.top()].parent = i;
        	st.pop();
    	}
    	st.push(i);
    	for(Query q : container[i]){
        	answer[q.idx] = arr[find(q.L,s)];
    	}
	}
	return 0;
}