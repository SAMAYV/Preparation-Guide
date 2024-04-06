/*

Given a sequence of n numbers a1, a2, ..., an and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). 
For each d-query (i, j), you have to return the number of distinct elements in the subsequence ai, ai+1, ..., aj.

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

int main() 
{
	ll n,q;
	cin>>n;
	ll arr[n+1];	
	REP(i,1,n+1){
		cin>>arr[i];
	}
	cin>>q;
	distinct c[q];
	REP(i,0,q){
		cin>>c[i].l>>c[i].u;
		c[i].index = i;
	}
	sort(c,c+q,compare);
	ll ans[q] = {0};
	ll repeat[1000001];
	REP(i,0,1000001){
		repeat[i] = -1;
	}
	ll tree[n+1];
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