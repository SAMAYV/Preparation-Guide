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
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

string solve(string s) {
    string res = s;
    int len;

    // Create pre-process array for KMP
    // Reverse and append to original
    reverse(s.begin(), s.end()); 
    // To avoid already palindrome cases
    
    s = res + "#" + s;
    
    ll arr[s.size()];
    arr[0] = 0;

    int i=0, j=1;

    len = s.length();
    while(j < len){
        if(s[i] == s[j]){
            arr[j] = i+1;
            i++; j++;
        } else {
            if(i>=1){
                i = arr[i-1];
            }else{
                arr[j] = 0;
                j++;
            }
        }
    }

    // cout<<arr[len-1]<<endl;
    return res.substr(0,arr[len-1]);
}
string reverseStr(string str) 
{ 
    int n = str.length(); 
  
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]);

    return str; 
} 
int main() 
{ 
    ll t;
    cin>>t;
    while(t--){
    	string s,out;
    	cin>>s;
    	string s1 = solve(s);
    	string s2 = reverseStr(s);
    	string s3 = solve(s2);
    	ll i = 0,j = s.size() - 1;
    	while(i < j && s[i] == s[j]){
    		i++;
    		j--;
    	}
    	if(i > j || i == j){
    		cout<<s<<endl;
    		continue;
    	}
    	string s4 = s.substr(i,j-i+1);
    	// cout<<s4<<endl;
    	string s5 = reverseStr(s4);
    	string s6 = solve(s4);
    	// cout<<s6<<endl;
    	string s7 = solve(s5);
    	s6 = s.substr(0,i) + s6 + s.substr(j+1);
    	s7 = s.substr(0,i) + reverseStr(s7) + s.substr(j+1);
    	if(s6.size() > s7.size())
    		out = s6;
    	else 
    		out = s7;
    	if(s1.size() > s3.size()){
    		if(s1.size() > out.size())
    			out = s1;
    	}
    	else {
    		if(s3.size() > out.size())
    			out = s3;
    	}
    	cout<<out<<endl;
    }
	return 0;	
} 
