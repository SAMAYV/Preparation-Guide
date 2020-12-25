#include <bits/stdc++.h>
using namespace std;
int main()
{
	string a,b;
	cin>>a>>b;
	int cost = 0;
	for(int i=0;i<a.length;i++){
		if(a[i]==b[i])
			continue;
		else {
			if(a[i]==a[i+1]){
				a[i] = '1' - a[i];
				cost++;
			}
			if(a[i]!=a[i+1]){
				if(a[i+1]==b[i+1]){
					a[i] = '1' - a[i];
				}
				else {
					a[i] = '1' - a[i];
					a[i+1] = '1' - a[i+1];
					cost++;
					i++;
				}
			}
		}
	}
	cout<<cost<<endl;
}