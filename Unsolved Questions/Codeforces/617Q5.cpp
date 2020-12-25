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
	int n;
	cin>>n;
	string s;
	cin>>s;
	string out = "0";
	vector<pair<char,int>> v;
	v.push_back({s[0],0});
	string p = "0";
	REP(i,1,n){
		v.push_back({s[i],i});
		sort(v.begin(),v.end());
		int j;

		int st = 0,ed = v.size()-1;
		while(st<=ed){
			int mid = (st+ed)/2;
			if(v[mid].first == s[i] && v[mid].second == i){
				j = mid;
				break;
			}
			else if(v[mid].first <= s[i])
				st = mid+1;
			else
				ed = mid-1;
		}


		//let position of s[i] after sorting is j
		if(j==i){
			out.push_back('0');
			p.push_back('0');
		}
		else {
			char q = out[j];
			for(int k=j+1;k<i;k++){
				if(out[k]!=q){
					cout<<"NO"<<endl;
					return 0;
				}
			}
			out.push_back(out[i-1]);
			p.push_back('1'+'0'- q);
			for(int k=i-1;k>j;k--){
				out[k] = out[k-1];
			}
			out[j] = '1'+'0'- q;
		}
	}
	cout<<"YES"<<endl;
	cout<<p<<endl;
	return 0;
}