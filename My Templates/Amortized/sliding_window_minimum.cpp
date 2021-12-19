#include <bits/stdc++.h>
using namespace std;

#define int long long

void sliding_window_min(int n,int k,int arr[]){
	deque<int> q;
	q.push_back(arr[0]);
	for(int i = 1; i < k; i++){
		while(q.size() > 0 && q.back() >= arr[i]){
			q.pop_back();
		}
		q.push_back(arr[i]);
	}
	vector<int> v;
	v.push_back(q.front());
	for(int i = k; i < n; i++){
		if(q.size() > 0 && q.front() == arr[i - k]){
			q.pop_front();
		}
		while(q.size() > 0 && q.back() >= arr[i]){
			q.pop_back();
		}
		q.push_back(arr[i]);
		v.push_back(q.front());	
	}
	for(auto it:v) cout<<it<<" ";
	cout<<endl;
}
int main() 
{ 
	int n,k;
	cin>>n>>k;
	int arr[n];
	for(int i = 0; i < n; i++){
		cin>>arr[i];
	}	
	sliding_window_min(n,k,arr);
	return 0;	 
} 