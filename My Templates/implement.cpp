void solve(){
    ll n, c;
    cin>>n>>c;
    map<pair<ll,ll>,vector<pair<ll,ll>>> cont;
    REP(i,0,n){
  	   ll x,y;
  	   cin>>x>>y;
  	   cont[make_pair(x - y, ((x % c) + c) % c)].emplace_back(x, y);
    }
    ll checkpoint = cont.size();
    ll moves = 0;
    for(auto i : cont){
  	   auto v = i.second;
  	   sort(v.begin(), v.end());
  	   auto pivot = v[v.size() / 2];
  	   for(auto j : v){
  	       moves += abs(pivot.first - j.first) / c;
  	   }
    }
    cout<<checkpoint<<" "<<moves<<endl;
}

int main() 
{
    ll t;
    cin>>t;
    while(t--){
	     solve();
    }
    return 0;
}