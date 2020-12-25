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

struct subset {
	int rank;
	int parent;
	int size;
};

void initialise(subset* s,ll n){
	REP(i,0,n){
		s[i].parent = i;
		s[i].rank = 0;
		s[i].size = 1;
	}
}

int find(int x,subset* s){
	if(s[x].parent==x)
		return x;
	s[x].parent = find(s[x].parent,s);
	return s[x].parent;
}

// union by rank
void unio(int x,int y,subset* s){
	int p1 = find(x,s);
	int p2 = find(y,s);
	if(s[p1].rank == s[p2].rank){
		s[p1].rank++;
		s[p2].parent = p1;
	}
	else if(s[p1].rank > s[p2].rank){
		s[p2].parent = p1;
	}
	else {
		s[p1].parent = p2;	
	}
}

// union by size
void unio(int x,int y,subset* s){
    int p1 = find(x,s);
	int p2 = find(y,s);
	if(s[p1].size >= s[p2].size){
		s[p2].parent = p1;
		s[p1].size += s[p2].size;
	}
	else {
		s[p1].parent = p2;	
		s[p2].size += s[p1].size;
	}
}

int main()
{
	
	return 0;
}