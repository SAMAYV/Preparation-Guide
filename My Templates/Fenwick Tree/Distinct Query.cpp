#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
#define ll long long int
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
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

/*

Given a sequence of n numbers a1, a2, ..., an and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence ai, ai+1, ..., aj.
Input

Line 1: n (1 ≤ n ≤ 30000).
Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 10^6).
Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

Output

For each d-query (i, j), print the number of distinct elements in the subsequence ai, ai+1, ..., aj in a single line.

Sample Input

5
1 1 2 1 3
3
1 5
2 4
3 5

Sample Output

3
2
3 

*/

struct distinct {
	ll l,u,index;
};

bool compare(distinct d1,distinct d2){
	if(d1.u == d2.u)
		return d1.l < d2.l;
	return d1.u < d2.u;
}
void update(ll* tree,ll ind,ll val,ll n){
	for(int i=ind;i<n;i+=(i&(-i))){
		tree[i] += val;
	}
}

ll query(ll* tree,ll ind,ll n){
	ll sum = 0;
	for(int i=ind;i>0;i-=(i&(-i))){
		sum += tree[i];
	}
	return sum;
}
int main() {

	ll n,q;
	cin>>n;
	ll* arr = new ll[n+1];	
	REP(i,1,n+1){
		cin>>arr[i];
	}
	cin>>q;
	distinct* c = new distinct[q];
	REP(i,0,q){
		cin>>c[i].l>>c[i].u;
		c[i].index = i;
	}
	sort(c,c+q,compare);
	ll* ans = new ll[q]();
	ll* repeat = new ll[1000001];
	REP(i,0,1000001){
		repeat[i] = -1;
	}
	ll* tree = new ll[n+1];
	ll j = 1;

	REP(i,0,q){
		ll start = c[i].l;
		ll end = c[i].u;
		while(j <= n && j <= end){
			if(repeat[arr[j]] != -1){
				update(tree,repeat[arr[j]],-1,n+1);
			}
			update(tree,j,1,n+1);
			repeat[arr[j]] = j;
			j++;
		}
		ans[c[i].index] = query(tree,end,n+1) - query(tree,start-1,n+1);
	}
	REP(i,0,q){
		cout<<ans[i]<<endl;
	}
	return 0;
}