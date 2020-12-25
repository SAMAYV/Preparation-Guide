/* find max abs(A[i]-A[j]) + abs(i-j) for pair(i,j) in A array*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int* a = new int[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	int val = 0;
	int addmaxi = n-1;  int addmaxv = a[n-1];
	int submaxi = n-1;  int submaxv = a[n-1];
	for(int i=n-2;i>=0;i--){
		val = max(max(addmaxv - a[i] + addmaxi - i , a[i] - submaxv + submaxi - i), val);
		int l1 = addmaxv + addmaxi;
		int l2 = submaxi - submaxv;
		int l3 = i + a[i];
		int l4 = i - a[i];
		
		if(l3 > l1){
			addmaxv = a[i];
			addmaxi = i;
		}
		if(l4 > l2){
			submaxv = a[i];
			submaxi = i;
		}
	}
	cout<<val<<endl;
	return 0;
}