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
#define MAX 1e6
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
// Function to reverse a string

int main()
{
	ll n;
	cin>>n;
	string o;
	getline(cin,o);
	while(n--){

		string s;
		getline(cin,s);
		vector<string> v,v1;
		
		stringstream k(s);
		string d;

		while(k >> d){
			v1.push_back(d);
		}

		ll b = 0;
		while(b < v1.size()){
			string l = v1[b];
			bool f = 0;
			REP(p,0,v1[b].size()){
			// ll p = 0;
				if(v1[b][p] >= 65 && v1[b][p] <= 90)
					l[p] = v1[b][p] + 32;
				else if(v1[b][p] >= 97 && v1[b][p] <= 122){

				}
				else f = 1;
			}
			v.push_back(v1[b]);
			
			if(f == 1){
				b++;
				continue;
			}

			ll j = b + 1;
			while(j < v1.size()){
				string r = v1[j];
				// p = 0;
				REP(p,0,v1[j].size()){
					if(v1[j][p] >= 65 && v1[j][p] <= 90)
						r[p] = v1[j][p] + 32;
				}
				if(r != l){
					break;
				}
				j++;
			}
			b = j;
		}
		
		REP(j,0,v.size()){
			cout<<v[j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
         
