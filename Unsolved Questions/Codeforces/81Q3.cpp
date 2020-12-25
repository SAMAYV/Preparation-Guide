#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ll long long
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
int main()
{
	int t;
	cin>>t;
	while(t--){
		string s,T;
		cin>>s>>T;
		vector<pair<char,int>> v;
		REP(i,0,s.size()){
			v.push_back({s[i],i});
		}
		sort(v.begin(),v.end());

		int i = 0, j = 0;
		ll ct = 1;
		while(i < T.size()){
			if(j>=s.size()){
				ct++;
				j = 0;
			}
			int place = INT_MAX;
			char search = T[i];
			int st = 0;
			int ed = s.size()-1;
			while(st <= ed){
				int mid = (st+ed)/2;
				if(v[mid].first == search && v[mid].second >= j){
					place = min(place,v[mid].second);
					ed = mid - 1;
				}
				else if(v[mid].first == search && v[mid].second < j){
					st = mid + 1;
				}
				else if(v[mid].first < search){
					st = mid + 1;
				}
				else {
					ed = mid - 1; 
				}
			}
			if(place == INT_MAX && j!=0){
				j = 0;
				ct++;
			}
			else if(place == INT_MAX && j==0){
				cout<<-1<<endl;
				break;
			}
			else {
				j = place+1;
				i++;
			}
		}
		if(i==T.size())
			cout<<ct<<endl;
	}
	return 0;
}