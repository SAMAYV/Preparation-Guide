#include <bits/stdc++.h>
using namespace std;
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

int a;
tuple<bool,int,int> DP(int** arr,int n,int m,int val){
	int** temp = new int*[n];
	unordered_map<int,bool> um;
	vector<pair<int,int>> q;
	REP(i,0,n){
		temp[i] = new int[m];
		int v = 0;
		int p = (a+1)/2;
		REP(j,0,m){
			temp[i][j] = (arr[i][j]>=val);
			v += p*temp[i][j];
			p /= 2;
		}
		if(!um.count(v)){
			q.push_back({v,i});
			um[v] = true;
		}
	}
	// cout<<endl;
	// REP(i,0,n){
	// 	REP(j,0,m){
	// 		cout<<temp[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// REP(i,0,q.size()){
	// 	cout<<q[i].first<<" "<<q[i].second<<endl;
	// }
	// cout<<endl;
	REP(i,0,q.size()){
		REP(j,i,q.size()){
			// cout<<(q[i].first | q[j].first)<<" ";
			if((q[i].first | q[j].first) == a){
				tuple<bool,int,int> tk = make_tuple(true,q[i].second,q[j].second);
				return tk;
			}
		}
	}
	cout<<endl;

	REP(i,0,n){
		delete [] temp[i];
	}
	return make_tuple(false,-1,-1);
}
tuple<int,int,int> binary(int** arr,int n,int m,int l,int u){
	int ans = 0;
	int i = -1, j = -1;
	while(l<=u){
		int mid = (l+u)/2;
		// int mid = 1;
		tuple<bool,int,int> t = DP(arr,n,m,mid);
		if(get<0>(t) ==false){
			u = mid-1;
			// cout<<mid<<"y"<<endl;
		}
		else {
			if(mid >= ans){
				ans = mid;
				i = get<1>(t); j = get<2>(t);
			}
			// cout<<mid<<"n"<<endl;
			l = mid+1;
		}
	}
	return make_tuple(ans,i,j);
}
int main()
{
	int n,m;
	cin>>n>>m;
	a = pow(2,m) - 1;
	int** arr = new int* [n];
	int maxi = 0;
	REP(i,0,n){
		arr[i] = new int[m];
		REP(j,0,m){
			cin>>arr[i][j];
			if(arr[i][j] > maxi)
				maxi = arr[i][j];
		}
	}
	tuple<int,int,int> tt = binary(arr,n,m,0,maxi);
	cout<<get<1>(tt) + 1<<" "<<get<2>(tt) + 1<<endl;
	return 0;
}

























