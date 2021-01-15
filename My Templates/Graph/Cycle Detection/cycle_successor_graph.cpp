void cycle(ll* edges,ll x,ll n){
	ll a = edges[x];
	ll b = edges[edges[x]];
	ll k = 0;
	while(a != b && k <= n){
		k++;
		a = edges[a];
		b = edges[edges[b]];
	}
	if(a != b){
		cout<<"NO CYCLE"<<endl;
		return;
	}
	a = x;
	while(a != b){
		a = edges[a];
		b = edges[b];
	}
	ll start = a;
	ll length = 1;
	ll end = edges[a];
	while(start != end){
		end = edges[end];
		length++;
	}
	cout<<"Start: "<<start<<endl;
	cout<<length<<endl;
}

int main() 
{ 
	ll n;
	cin>>n;
	ll edges[n+1];
	REP(i,1,n+1){
		cin>>edges[i];
	}
	ll x;
	cin>>x;
	cycle(edges,x,n);
	return 0;	
} 
