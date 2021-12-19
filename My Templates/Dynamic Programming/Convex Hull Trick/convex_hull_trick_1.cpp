// https://codeforces.com/contest/1083/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define ld long double

struct line {
    ll m, c;
    ll eval(ll x){ 
    	return m*x + c; 
    }
    ld intersectX(line l){ 
    	return (ld)(c - l.c)/(l.m - m); 
    }
};

struct rectangle {
	ll p,q,a;
};

bool compare(rectangle a,rectangle b){
	return a.p < b.p;
}

deque<line> d;
auto cmp = [&d](ll idx,ll x){ 
	return d[idx].intersectX(d[idx + 1]) < x; 
};

ll convex_hull_trick(rectangle* rect,ll n){
	d.push_back({0,0});
	ll ans = 0;

	// p are in increasing order and q are in decreasing order
	// slopes are coming in decreasing order and lines are inserted in deque in increasing order of slope
	// queries are coming in decreasing order of x 
	for(int i = 0; i < n; i++){
		while(d.size() >= 2 && d[d.size()-1].eval(rect[i].q) <= d[d.size()-2].eval(rect[i].q)){
			d.pop_back();
		}
		ll f = d[d.size()-1].eval(rect[i].q) + rect[i].p*rect[i].q - rect[i].a;
		ans = max(ans,f);
		line curr = {-rect[i].p,f};
		while(d.size() >= 2 && d[0].intersectX(d[1]) <= d[0].intersectX(curr)){
			d.pop_front();
		}
		d.push_front(curr);
	}

	// The lines are inserted in sorted order of slopes
	// The query positions are in arbitrary order
	vector<ll> ints(n);
	for(int i = 0; i < n; i++){
		ints[i] = i;	
	} 
	for(int i = 0; i < n; i++){
		ll idx = *lower_bound(ints.begin(),ints.begin() + d.size() - 1, rect[i].q, cmp);
		ll f = d[idx].eval(rect[i].q) + rect[i].p*rect[i].q - rect[i].a;
		ans = max(ans,f);
		line curr = {-rect[i].p,f};
		while(d.size() >= 2 && d[0].intersectX(d[1]) <= d[0].intersectX(curr)){
			d.pop_front();
		}
		d.push_front(curr);
	}
	return ans;
}

int main()
{
	ll n;
	cin>>n;
	rectangle rect[n];
	for(int i = 0; i < n; i++){
		cin>>rect[i].p>>rect[i].q>>rect[i].a;
	}
	sort(rect,rect+n,compare);
	cout<<convex_hull_trick(rect,n)<<endl;
    return 0;
}