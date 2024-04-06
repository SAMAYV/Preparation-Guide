// https://www.codechef.com/problems/CHGM
int main()
{
	i_os;
    ll t;
    cin>>t;
    while(t--){
    	ll n;
    	char ch;
    	cin>>n>>ch;
    	if(n % 2 == 0){
    		if(ch == 'T') cout<<"T-Series\n";
    		else cout<<"PewDiePie\n";
    	}
    	else {
    		if(ch == 'P') cout<<"T-Series\n";
    		else cout<<"PewDiePie\n";
    	}
    }
    return 0;
}