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

/*

Gary has two string S and V. Now Gary wants to know the length shortest subsequence in S such that it is not a subsequence in V.
Note: input data will be such so there will always be a solution.
Input Format :

Line 1 : String S of length N (1 <= N <= 1000)
Line 2 : String V of length M (1 <= M <= 1000)

Output Format :

Length of shortest subsequence in S such that it is not a subsequence in V

Sample Input :

babab
babba

Sample Output :

3

*/

int mem(string S,string V,int** out){
    
    int s = S.size();
    int v = V.size();
    
    //base case
    if(S.size()==0)
        return -1;
    if(V.size()==0)
        return 1;
    
    //checking ans already exists?
    if(out[s][v] != -2)
        return out[s][v];
    
    //small calculation
    int i,s1,s2;
    
    s1 = mem(S.substr(1),V,out);
    
    for(i=0;i<V.size();i++){
        if(V[i]==S[0])
            break;
    }
    if(i==V.size())
        s2 = 0;
    else 
         s2 = mem(S.substr(1),V.substr(i+1),out);   
    
    if(s2!=-1)
        s2 += 1;
    
    //saving answer
    if(s1==-1 && s2!=-1)
        out[s][v] = s2;
    else if(s1!=-1 && s2==-1)
        out[s][v] = s1;
    else if(s1!=-1 && s2!=-1)
        out[s][v] = min(s1,s2);
    else
        out[s][v] = -1;
    
    //returning answer
    return out[s][v];
}
int DP(string S,string V,int** out){
    int s = S.size();
    int v = V.size();
    
    for(int i=0;i<v+1;i++){
        out[0][i] = -1;
    }
    for(int i=1;i<s+1;i++){
        out[i][0] = 1;
    }
    for(int i=1;i<s+1;i++){
        for(int j=1;j<v+1;j++){
            int ele = S[s-i];
            string str = V.substr(v-j);
            
            int k;
            for(k=0;k<str.size();k++){
                if(ele==str[k])
                    break;
            }
            int m,n;
            n = out[i-1][j];
            if(k!=str.size())
                m = out[i-1][str.size()-k-1];
            else
                m = 0;
        
            if(m!=-1 && n!=-1){
                out[i][j] = min(1 + m,n);
            }
            else if(m==-1 && n!=-1){
                out[i][j] = n;
            }
            else if(m!=-1 && n==-1){
                out[i][j] = m+1;
            }
            else
                out[i][j] = -1;
            }
    }
    return out[s][v];
}
int solve(string S,string V)
{
    int s = S.size();
    int v = V.size();
	int** out = new int*[s + 1];
    for(int i=0;i<s+1;i++){
        out[i] = new int[v+1];
        for(int j=0;j<v+1;j++)
            out[i][j] = -2;
    }
    return mem(S,V,out);
    return DP(S,V,out);
}
int main()
{
	    
    return 0;
}        
