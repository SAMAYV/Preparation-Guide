// https://codeforces.com/problemset/problem/319/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> {
    bool bad(iterator y){
        auto z = next(y);
        if(y == begin()){
            if(z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if(z == end()) return y->m == x->m && y->b <= x->b;
        return 1.0*(x->b - y->b)*(z->m - y->m) >= 1.0*(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b){
        auto y = insert({m, b});
        y->succ = [=]{
        	return next(y) == end() ? 0 : &*next(y);
        };
        if(bad(y)){
        	erase(y);
        	return;
        }
        while(next(y) != end() && bad(next(y))) erase(next(y));
        while(y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x){
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};
int main()
{
    ll t;
    t = 1;
    while(t--){
        ll n;
        cin>>n;
        ll a[n],b[n];
        for(int i = 0; i < n; i++) cin>>a[i];
        for(int i = 0; i < n; i++) cin>>b[i];
        HullDynamic h;
        h.insert_line(-b[0],-0);
        ll ans;
        for(int i = 1; i < n; i++){
        	ll p1 = h.eval(a[i]);
        	h.insert_line(-b[i],p1);
        }
        cout<<-h.eval(a[n-1])<<endl;
    }
}