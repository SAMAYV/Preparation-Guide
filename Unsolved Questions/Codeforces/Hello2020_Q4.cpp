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
typedef pair<ll,pair<ll,ll>> pp;

class compare1{
	public:
	bool operator () (pp a, pp b) {
		return a.second.first > b.second.first;
	}
};
class compare2{
	public:
	bool operator () (pp a, pp b) {
		return a.second.second < b.second.second;
	}
};
ll max(ll a,ll b){
	return a > b ? a : b;
}
ll min(ll a,ll b){
	return a < b ? a : b;
}
int main()
{
	ll n;
	cin>>n;
	multimap<ll,pair<ll,bool>> um;
	pair<ll,ll> p[n],p1[n];
	REP(i,0,n){
		cin>>p[i].first>>p[i].second>>p1[i].first>>p1[i].second;
		um.insert({p[i].first, make_pair(i,true)});
		um.insert({p[i].second + 1, make_pair(i,false)});
	}
	multiset<pp> s;
	unordered_map<ll,bool> um1;
	priority_queue<pp,vector<pp>,compare1> pq;
	priority_queue<pp,vector<pp>,compare2> pq1;
	ll minx = 0;
	ll maxx = 0;
	for(auto i=um.begin();i!=um.end();i++){
		// cout<<i->first<<" "<<(i->second).first<<endl;
		ll data = i->first;
		ll ind = (i->second).first;
		if((i->second).second == true)
		{
			if(pq.empty()){
				minx = p1[ind].first;	
			}
			if(pq1.empty()){
				maxx = p1[ind].second;
			}
			if(p1[ind].first <= maxx && minx <= p1[ind].second){
				s.insert({ind , p1[ind]});
				pq.push({ind , p1[ind]});
				pq1.push({ind , p1[ind]});
				minx = min(p1[ind].first , minx);
				maxx = max(p1[ind].second , maxx);		
			}
			else {
				cout<<"NO"<<endl;
				return 0;
			}
		}
		else {
			um1[ind] = true;
			s.erase({ind,p1[ind]});
		}

		while(!pq.empty()){
			pp pt1 = pq.top();
			if(um1.count(pt1.first))
				pq.pop();
			else {
				minx = pt1.second.first;
				break;
			}
		}
		
		while(!pq1.empty()){
			pp pt2 = pq1.top();
			if(um1.count(pt2.first))
				pq1.pop();
			else {
				maxx = pt2.second.second;
				break;
			}
		}
	}

	multimap<ll,pair<ll,bool>> um3;
	multiset<pp> s2;
	unordered_map<ll,bool> um2;
	priority_queue<pp,vector<pp>,compare1> pq2;
	priority_queue<pp,vector<pp>,compare2> pq3;
	minx = 0; maxx = 0;

	REP(i,0,n){
		um3.insert({p1[i].first, make_pair(i,true)});
		um3.insert({p1[i].second + 1, make_pair(i,false)});
	}

	for(auto i=um3.begin();i!=um3.end();i++){
		// cout<<i->first<<" "<<(i->second).first<<endl;
		ll data = i->first;
		ll ind = (i->second).first;
		if((i->second).second == true)
		{
			if(pq2.empty()){
				minx = p[ind].first;	
			}
			if(pq3.empty()){
				maxx = p[ind].second;
			}
			if(p[ind].first <= maxx && minx <= p[ind].second){
				s2.insert({ind , p[ind]});
				pq2.push({ind , p[ind]});
				pq3.push({ind , p[ind]});
				minx = min(p[ind].first , minx);
				maxx = max(p[ind].second , maxx);		
			}
			else {
				cout<<"NO"<<endl;
				return 0;
			}
		}
		else {
			um2[ind] = true;
			s2.erase({ind,p[ind]});
		}

		while(!pq2.empty()){
			pp pt1 = pq2.top();
			if(um2.count(pt1.first))
				pq2.pop();
			else {
				minx = pt1.second.first;
				break;
			}
		}
		
		while(!pq3.empty()){
			pp pt2 = pq3.top();
			if(um2.count(pt2.first))
				pq3.pop();
			else {
				maxx = pt2.second.second;
				break;
			}
		}
	}
	cout<<"YES"<<endl;
	return 0;
}