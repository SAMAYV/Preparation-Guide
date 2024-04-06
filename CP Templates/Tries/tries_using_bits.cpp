/*

A straightforward question. Given an array of positive integers you have to print the number of subarrays whose XOR is less than K. 
Subarrays are defined as a sequence of continuous elements Ai, Ai+1, ..., Aj . XOR of a subarray is defined as Ai ^ Ai+1 ^ ... ^ Aj. 
Symbol ^ is Exclusive Or.

Input Format
First line contains T, the number of test cases. 
Each of the test case consists of N and K in one line, followed by N space separated integers in next line.

Output Format
For each test case, print the required answer.

Constraints:
1 ≤ T ≤ 5
1 ≤ N ≤ 10^5
1 ≤ A[i] ≤ 10^5
1 ≤ K ≤ 10^6

Sample Input
1
5 2
4 1 3 2 7   

Sample Output
3

*/

class TrieNode {
	public:
		ll data;
		TrieNode* left;
		TrieNode* right;
		TrieNode(){
			this->left = NULL;
			this->right = NULL;
			this->data = 0;
		}
};

void insert(TrieNode* root,ll val){
	TrieNode* curr = root;
	REPI(i,0,60){
		ll v = (val >> i) & 1;
		if(v == 1){
			if(!curr->right){
				curr->right = new TrieNode();
			}
			curr->right->data++;
			curr = curr->right;
		}
		else {
			if(!curr->left){
				curr->left = new TrieNode();
			}
			curr->left->data++;
			curr = curr->left;	
		}
	}
}

ll compute(TrieNode* root,ll* arr,ll val,ll k){
	TrieNode* curr = root;
	ll sum = 0;
	REPI(i,0,60){
		ll v1 = (val >> i) & 1;
		ll v2 = (k >> i) & 1;
		if(v1 == 1 && v2 == 1){
			if(curr->right)
				sum += curr->right->data;
			if(curr->left)
				curr = curr->left;
			else
				return sum;
		}
		else if(v2 == 1){
			if(curr->left)
				sum += curr->left->data;
			if(curr->right)
				curr = curr->right;
			else
				return sum;
		}
		else if(v1 == 1){
			if(curr->right)
				curr = curr->right;
			else
				return sum;
		}
		else {
			if(curr->left)
				curr = curr->left;
			else
				return sum;
		}
	}
	if(curr) sum += curr->data;
	return sum;
}

ll subxor(TrieNode* root,ll* arr,ll n,ll k){
	ll x[n];
	ll count = 0;
	REP(i,0,n){
		x[i] = arr[i];
		if(i > 0) x[i] ^= x[i-1];
		if(x[i] < k) count++;
		count += compute(root,arr,x[i],k);
		insert(root,x[i]);
	}
	return count;
}

int main()
{
	ll t;
	cin>>t;
	while(t--){
		ll n,k;
		cin>>n>>k;
		ll arr[n];
		REP(i,0,n){
			cin>>arr[i];
		}
		TrieNode* root = new TrieNode();
		cout<<subxor(root,arr,n,k)<<endl;
	}
	return 0;
}