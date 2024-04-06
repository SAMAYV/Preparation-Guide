// https://codeforces.com/contest/1284/problem/D

struct Query {
	ll t,s,e,f;
};
bool compare(Query a,Query b){
	if(a.t == b.t) return a.f < b.f;
	return a.t < b.t;
}

bool check(vector<ll>& sa,vector<ll>& ea,vector<ll>& sb,vector<ll>& eb,ll n){
	multiset<ll> s,e;
	vector<Query> v;
	REP(i,0,n){
		Query q;
		q.t = sa[i]; q.s = sb[i]; q.e = eb[i]; q.f = 1;
		v.push_back(q);
		q.t = ea[i] + 1; q.s = sb[i]; q.e = eb[i]; q.f = 0;
		v.push_back(q);
	}
	sort(v.begin(),v.end(),compare);
	REP(i,0,2*n){
		if(v[i].f == 1){
			if(s.size()){
				ll maxs = *s.rbegin();
				ll mine = *e.begin();
				if(maxs > v[i].e || mine < v[i].s) return 0;
			}
			s.insert(v[i].s);
			e.insert(v[i].e);
		}
		else {
			s.erase(s.find(v[i].s));
			e.erase(e.find(v[i].e));
		}
	}
	return 1;
}
int main()
{
	i_os;
	ll n;
	cin>>n;
	vector<ll> sa(n),ea(n),sb(n),eb(n);
	REP(i,0,n){
		cin>>sa[i]>>ea[i]>>sb[i]>>eb[i];
	}
	if(check(sa,ea,sb,eb,n) && check(sb,eb,sa,ea,n)) cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}