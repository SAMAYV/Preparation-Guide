/*

In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations
INSERT(S,x): if x is not in S, insert x into S
DELETE(S,x): if x is in S, delete x from S

and the two type of queries
K-TH(S) : return the k-th smallest element of S
COUNT(S,x): return the number of elements of S smaller than x

Input Format
Line 1: Q (1 ≤ Q ≤ 200000), the number of operations
In the next Q lines, the first token of each line is a character I, D, K or C meaning that the corresponding operation is 
INSERT, DELETE, K-TH or COUNT, respectively, following by a whitespace and an integer which is the parameter for that operation.

If the parameter is a value x, it is guaranteed that ≤ |x| ≤ 10^9. If the parameter is an index k, it is guaranteed that 1 ≤ k ≤ 10^9.`

Output
For each query, print the corresponding result in a single line. In particular, for the queries K-TH, if k is larger than the number of elements in S, print the word 'invalid'.

Input Format
8
I -1
I -1
I 2
C 0
K 2
D -1
K 1
K 2

Output Format
1
2
2
invalid

*/

struct coordinate {
	char ch;
	ll val;
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

int main() 
{
	ll q;
	cin>>q;
	vector<ll> v,v1;
	coordinate arr[q];
	REP(i,0,q){
		cin>>arr[i].ch>>arr[i].val;
		if(arr[i].ch == 'I'){
			v.push_back(arr[i].val);
		}
	}
	sort(v.begin(),v.end());
	map<ll,ll> um,umm;
	ll j = 1;

	REP(i,0,v.size()){
		if(!um.count(v[i])){
			um[v[i]] = j;
			v1.push_back(v[i]);
			j++;
		}
	}
	ll a[v.size()];
	ll tree[j+2];

	// 0 for new
	// 1 for present
	// 2 for deleted
	REP(i,0,q){
		if(arr[i].ch == 'I'){
			if(umm[arr[i].val] == 2 || umm[arr[i].val] == 0){
				umm[arr[i].val] = 1;
				ll rank = um[arr[i].val];
				update(tree,rank,1,j);
			}
		}
		else if(arr[i].ch == 'D'){
			if(umm[arr[i].val] == 1){
				ll rank = um[arr[i].val];
				update(tree,rank,-1,j);
				umm[arr[i].val] = 2;
			}
		}
		else if(arr[i].ch == 'C'){
			ll id = lower_bound(v1.begin(),v1.end(),arr[i].val) - v1.begin();
			cout<<query(tree,id,j)<<endl;
		}
		else {
			ll lower = 0;
			ll upper = v1.size()-1;
			ll mini = INT_MAX;
			while(lower <= upper){
				ll mid = (lower+upper)/2;
				ll value = v1[mid];
				ll ans = query(tree,mid,j);
				if(ans == arr[i].val){
					mini = min(mini,mid);
					upper = mid-1;
				}
				else if(ans > arr[i].val){
					upper = mid-1;
				}
				else {
					lower = mid+1;
				}
			}
			if(mini == INT_MAX) cout<<"invalid"<<endl;
			else cout<<v1[mini]<<endl;
		}
	}
	return 0;
}