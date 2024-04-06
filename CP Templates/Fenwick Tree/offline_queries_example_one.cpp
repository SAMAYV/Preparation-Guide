/*
Given a sequence of n numbers a1, a2, ..., an and a number of k- queries. A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). 
For each k-query (i, j, k), you have to return the number of elements greater than k in the subsequence ai, ai+1, ..., aj.

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
	for(ll i = ind; i <= n;i += (i & (-i))){
		tree[i] += val;
	}
}
ll query(ll* tree,ll ind,ll n){
	ll sum = 0;
	for(ll i = ind; i > 0; i -= (i & (-i))){
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

int main() 
{
	ll n,q;
	cin>>n;
	coordinate arr[n+1];
	REP(i,1,n+1){
		cin>>arr[i].val;
		arr[i].index = i;
	}
	sort(arr+1,arr+n+1,comp);
	cin>>q;
	kquery p[q];
	REP(i,0,q){
		cin>>p[i].i1>>p[i].j1>>p[i].k1;
		p[i].ind = i;
	}
	sort(p,p+q,compare);

	ll i = 0,j = 1;
	ll ans[q];
	ll tree[n+1];

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