#include <bits/stdc++.h>
using namespace std;
int* getlps(string T){
	int t = T.length();
	int* lps = new int[t];
	lps[0] = 0;
	int i = 1;
	int j = 0;
	while(i < t){
		if(T[i]==T[j]){
			lps[i] = j + 1;
			i++;
			j++;
		}
		else {
			if(j==0){
				i++;
			} else {
				j = lps[j-1];
			}
		}
	}
	return lps;
}
void kmp(string S,string T){
	int s = S.length();
	int t = T.length();
	int* lps = getlps(T);
	vector<int> v;
	int i = 0;
	int j = 0;
	int k = 0;
	while(1){
		if(j==t){
			v.push_back(k);
			j = lps[j-1];
			k = i -j;
		}
		if(i==s)
			break;
		if(S[i]==T[j]){
			i++;
			j++;
		}
		else {
			if(j==0){
				i++;
				k++;
			}
			else {
				j = lps[j-1];
				k = i - j;
			}
		}
	}
	for(auto i : v)
		cout<<i<<" ";
}
int main()
{
	string S,T;
	getline(cin,S);
	getline(cin,T);
	kmp(S,T);
	return 0;
}