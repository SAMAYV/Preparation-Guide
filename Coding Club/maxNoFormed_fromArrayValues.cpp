#include <bits/stdc++.h>
using namespace std;
#define REP(i,f,n) for(int i=0;i<n;i+=f)

bool compare(string s1,string s2){
	int l1 = s1.size();
	int l2 = s2.size();
	int mi = min(l1,l2);
	int i = 0;
	while(i < mi){
		if(s1[i] > s2[i])
			return true;
		else if(s1[i] < s2[i])
			return false;
		i++;
	}
	if(i==mi)
	{
		if(i==l1){
			while(i<l2){
				if(s2[i] > s2[i-mi])
					return false;
				else if(s2[i] < s2[i-mi])
					return true;
				i++;
			}
		}
		else if(i==l2){
			while(i<l1){
				if(s1[i] > s1[i-mi])
					return true;
				else if(s1[i] < s1[i-mi])
					return false;
				i++;
			}
		}
		if(i==l2)
			return true;
	}
}
int main()
{
	int n;
	cin>>n;
	string* a = new string[n];

	REP(i,1,n){
		cin>>a[i];
	}
	sort(a,a+n,compare);
	string out = "";
	REP(i,1,n){
		// cout<<a[i]<<" ";
		out += a[i];
	}
	cout<<out<<endl;
	return 0;
}