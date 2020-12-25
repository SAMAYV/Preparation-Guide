#include<bits/stdc++.h>
using namespace std;
bool isvalid(int n,int k){
	int x = n;
	int sharma = 0;
	int singh = 0;
	while(x!=0){
		if(x<=k){
			sharma += x;
			x = 0;
			break;
		}
		sharma += k;
		x = x-k;
		singh += x/10;
		x = x - x/10;
	}
	if(sharma >= (n+1)/2)
		return true;
	else
		return false;
}
int solve(int n,int start,int end){
	int min = end;
	while(start<=end){
		int mid = (start+end)/2;
		if(isvalid(n,mid)){
			if(mid<min)
				min = mid;
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}
	return min;
}
int main()
{
    int n;
    cin>>n;
    cout<<solve(n,1,n);
	return 0;
}
