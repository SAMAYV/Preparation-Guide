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

Given a sequence of n numbers a1, a2, ..., an and a number of k- queries. A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query (i, j, k), you have to return the number of elements greater than k in the subsequence ai, ai+1, ..., aj.
Input Format

Line 1: n (1 ≤ n ≤ 30000).

Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 10^9).

Line 3: q (1 ≤ q ≤ 200000), the number of k- queries.

In the next q lines, each line contains 3 numbers i, j, k representing a k-query (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 10^9).

Output Format

For each k-query (i, j, k), print the number of elements greater than k in the subsequence ai, ai+1, ..., aj in a single line.

Sample Input

5
5 1 2 3 4
3
2 4 1
4 4 4
1 5 2 

Sample Output

2
0
3 

*/

struct coordinate {
	ll val;
	ll index;
};

struct kquery {
	ll k1,i1,j1,ind;
};

void update(ll* tree,ll ind,ll val,ll n){
	for(int i=ind;i<=n;i+=(i&(-i))){
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
bool compare(kquery q1,kquery q2){
	return q1.k1 > q2.k1;
}

bool comp(coordinate c1,coordinate c2){
	return c1.val > c2.val;
}

int main() {

	ll n,q;
	cin>>n;
	coordinate* arr = new coordinate[n+1];
	REP(i,1,n+1){
		cin>>arr[i].val;
		arr[i].index = i;
	}
	sort(arr+1,arr+n+1,comp);
	cin>>q;
	kquery* p = new kquery[q];
	REP(i,0,q){
		cin>>p[i].i1>>p[i].j1>>p[i].k1;
		p[i].ind = i;
	}
	sort(p,p+q,compare);

	ll i = 0,j = 1;
	ll* ans = new ll[q];
	ll* tree = new ll[n+1];

	while(i < q){
		while(j < n+1 && arr[j].val > p[i].k1){
			update(tree,arr[j].index,1,n);
			j++;
		}
		ans[p[i].ind] = query(tree,p[i].j1,n) - query(tree,p[i].i1-1,n);
		i++;
	}
	REP(i,0,q){
		cout<<ans[i]<<endl;
	}
	return 0;
}