class Extended {
	public:
	ll x,y,gcd;
};
Extended ExtendedEuclid(ll a,ll b){
	if(b == 0){
		Extended e;
		e.x = 1;
		e.y = 0;
		e.gcd = a;
		return e;
	}
	Extended small = ExtendedEuclid(b,a % b);
	Extended ans;
	ans.x = small.y;
	ans.y = small.x - (a/b)*small.y;
	ans.gcd = small.gcd;
	return ans;
}
ll mmInverse(ll a,ll m){
	Extended e = ExtendedEuclid(a,m);
	return (e.x + m) % m;
}
int main() 
{ 
	ll a,m;
	cin>>a>>m;
	// a and m should be coprime
	ll ans = mmInverse(a,m); //a inverse mod m
	cout<<ans<<endl;
	return 0;	 
} 