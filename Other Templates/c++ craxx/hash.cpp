//BROWNIE TK

#include <bits/stdc++.h>
typedef long long int lli;
typedef unsigned long long int ulli;
typedef long double ldb;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define pb push_back
#define popb pop_back()
#define pf push_front
#define popf pop_front()
#define si size()
#define be begin()
#define en end()
#define all(v) v.be, v.en
#define le length()
#define mp make_pair
#define mt make_tuple
#define acc(v) accumulate(all(v), 0)
#define F first
#define S second

#define forz(i, n) for (int i = 0; i < n; i++)
#define fore(i, m, n) for (int i = m; i <= n; i++)
#define rforz(i, n) for (int i = n - 1; i >= 0; i--)
#define rforzm(i, m, n) for (int i = n - 1; i >= m; i--)
#define deci(n) fixed << setprecision(n)
#define high(n) __builtin_popcount(n)
#define highll(n) __builtin_popcountll(n)
#define parity(n) __builtin_parity(n)
#define ctz(n) __builtin_ctz(n)
#define lb lower_bound
#define ub upper_bound
#define er equal_range
#define maxe *max_element
#define mine *min_element
#define mod 1000000007
#define mod2 998244353
#define gcd __gcd
#define kira ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl

#define oset tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define osetlli tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
#define ofk order_of_key
#define fbo find_by_order
using namespace std;

/*STD fucntions*/
const int N=1023;
const int INF =mod;
vector<vector<int>> hashvec(N,vector<int>(1,INF));
int hash_fun(int val){
	return val%N;
}
void insert(int key){
	int hkey=hash_fun(key);
	if(hashvec[hkey].size()==1 && hashvec[hkey][0]==INF){
		hashvec[hkey][0]=key;
	}
	else{
		hashvec[hkey].push_back(key);
	}

}
bool search(int key){
	int hkey=hash_fun(key);
	if(hashvec[hkey].size()==1 && hashvec[hkey][0]==INF) return false;
	
	for(int i=0;i<hashvec[hkey].size();i++){
		
		if(hashvec[hkey][i]==key){
			
			return true;
		}
	
	}
	return false;
}
bool delete_key(int key){
	if(!search(key)) return false;
	int hkey=hash_fun(key);
	
	int i=0;
	for (;i<hashvec[hkey].size();i++) {
		if(hashvec[hkey][i]==key) break;
	}
	if(i==hashvec[hkey].size()) return false;
	hashvec[hkey].erase(hashvec[hkey].begin()+i);
	return true;
}


int main(){
	insert(9214);
	insert(9041274);
	insert(4000);
	insert(1000);
	delete_key(1000);
	cout<<search(4000);

	return 0;
}
