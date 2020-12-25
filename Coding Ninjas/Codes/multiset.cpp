#include <bits/stdc++.h>
using namespace std;
int main()
{
	multiset<int> ms;
	for(int i=0;i<10;i++)
		ms.insert(1);
	for(int i=0;i<2;i++)
		ms.insert(3);
	for(int i=0;i<4;i++)
		ms.insert(2);

	for(auto x : ms)
		cout<<x<<" ";
	cout<<ms.count(1)<<endl;
	// ms.erase(ms.find(1));
	// ms.erase(2);
	// cout<<endl;
	// for(auto x : ms)
		// cout<<x<<" ";
	cout<<endl;
	auto it = ms.lower_bound(2);
	auto i = ms.upper_bound(2);
	if(it!=ms.begin())
		cout<<*it;
	return 0;
}