// Keeps upper hull for maximums. 
// Add lines with -m and -b and return -ans to make this code working for minimums. 

// https://codeforces.com/contest/1083/problem/E

struct rectangle {
	ll p,q,a;
};
bool compare(rectangle a,rectangle b){
	return a.p < b.p;
}

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
ll convex_hull_trick(rectangle* rect,ll n){
	ll ans = 0;
	HullDynamic h;
	h.insert_line(0,0);

	// The lines are inserted in arbitrary order of slope
	// The query positions are in arbitrary order
	REP(i,0,n){
		ll f = h.eval(rect[i].q) + rect[i].p*rect[i].q - rect[i].a;
		ans = max(ans,f);
		h.insert_line(-rect[i].p,f);
	}
	return ans;
}
int main()
{
	i_os;
	ll n;
	cin>>n;
	rectangle rect[n];
	REP(i,0,n){
		cin>>rect[i].p>>rect[i].q>>rect[i].a;
	}
	sort(rect,rect+n,compare);
	cout<<convex_hull_trick(rect,n)<<endl;
    return 0;
}