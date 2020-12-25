#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,f;
	cin>>n>>f;
	string* arr = new string[n];
	unordered_map<string,int> um;
	for(int i=0;i<n;i++){
		cin>>arr[i];
		um[arr[i]] = i;
	}
	ll c = 0;
	for(int i=0;i<=n-3;i++){
		string s1 = arr[i];
		for(int j=i+1;j<=n-2;j++){
			string s2 = arr[j];
			string s3 = "";
			for(int k=0;k<f;k++){
				if(s1[k]==s2[k])
					s3 += s1[k];
				else if(s1[k]=='S' && s2[k]=='E')
					s3 += 'T';
				else if(s1[k]=='S' && s2[k]=='T')
					s3 += 'E';
				else if(s1[k]=='T' && s2[k]=='E')
					s3 += 'S';
				else if(s1[k]=='T' && s2[k]=='S')
					s3 += 'E';
				else if(s1[k]=='E' && s2[k]=='T')
					s3 += 'S';
				else if(s1[k]=='E' && s2[k]=='S')
					s3 += 'T';
			}
			// cout<<s3<<" ";
			if(um.count(s3)){
				if(um[s3]>j)
					c++;
			}
		}
	}
	cout<<c<<endl;
	return 0;
}