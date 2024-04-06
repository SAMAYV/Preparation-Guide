#include <bits/stdc++.h>
using namespace std;

#define int long long

int main()
{
	int n;
	cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++) cin >> arr[i];

	// L stores at ith index the minimum ending index of increasing subsequence of length i+1 
	// Lv stores at ith index the minimum ending index value of increasing subsequence of length i+1
	// Lv will be increasing 

	int L[n],R[n],Lv[n];

	for(int i = 0; i < n; i++){
		L[i] = 1e18;
		Lv[i] = 1e18;
		R[i] = -1;
	}

	L[0] = 0;
	Lv[0] = arr[0];

	for(int i = 1; i < n; i++){
		int p = upper_bound(Lv,Lv+n,arr[i]) - Lv;
		Lv[p] = arr[i];
		L[p] = i;
		if(p > 0)
			R[i] = L[p-1];
		else 
			R[i] = -1;
	}

	int length = 1;
	for(int i = 0; i < n; i++){
		if(L[i] != 1e18) length = i+1;
	}
	cout << length << endl;

	vector<int> v;
	int curr = L[length-1];
	while(curr > -1){
		v.push_back(curr);
		curr = R[curr];
	}
	
	reverse(v.begin(),v.end());
	for(auto it:v) cout << it << " ";
	cout << endl;
	return 0;
}