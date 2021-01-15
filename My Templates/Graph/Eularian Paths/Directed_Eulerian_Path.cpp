#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

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
// SOME BITMASK KNOWLEDGE
// 1)x & (x - 1):sets the last one bit of x to zero
// power of two exactly when x & (x − 1) = 0.
// 2)x & -x:sets all the one bits to zero, except last one bit
// 3)x | (x - 1):inverts all the bits after the last one bit
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set1;
typedef tree<string,null_type,less<string>,rb_tree_tag,tree_order_statistics_node_update> indexed_set2;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);

ll power(ll a,ll n,ll c){
    if(n == 0) return 1 % c;
    ll s = power(a,n/2,c);
    s = (s * s) % c;
    if(n % 2) s = (s * a) % c;
    return s;
}

void Eularian_Path(set<ll>* edges,ll n){
    vector<ll> out_deg(n,0),in_deg(n,0);
    REP(i,0,n){
        for(auto it:edges[i]){
            out_deg[i]++;
            in_deg[it]++;
        }
    }
    ll first = 0;
    while(first < n && !deg[first]){
        first++;
    }
    if(first == n){
        cout<<-1<<endl;
        return;
    }
    ll v1 = -1, v2 = -1;
    bool bad = 0;
    REP(i,0,n){
        if(in_deg[i] != out_deg[i]){
            if(v1 != -1 && v2 != -1){
                bad = 1;
            }
            else if(in_deg[i] - out_deg[i] == 1){
                v1 = i;
            }
            else if(in_deg[i] - out_deg[i] == -1){
                v2 = i;
            }
            else {
                bad = 1;
            }
        }
    }
    if(bad){
        cout<<-1<<endl;
        return;
    }
    else if(v1*v2 < 0){
        cout<<-1<<endl;
        return;   
    }
    if(v1 != -1 && v2 != -1){
        edges[v1].insert(v2);
    }
    stack<ll> st;
    st.push(first);
    vector<ll> res;
    while(st.size()){
        ll v = st.top();
        if(edges[v].size() > 0){
            ll ver = *edges[v].begin();
            edges[v].erase(ver);
            st.push(ver); 
        }
        else {
            res.push_back(v);
            st.pop();
        }
    }
    reverse(res.begin(),res.end());
    if(v1 != -1){
        REP(i,0,res.size()){
            if(res[i] == v1 && res[i + 1] == v2){
                vector<ll> res2;
                REP(j,i+1,res.size()){
                    res2.push_back(res[j]);
                }
                REP(j,1,i+1){
                    res2.push_back(res[j]);
                }
                res = res2;
                break;
            }
        }
    }
    REP(i,0,n){
        if(edges[i].size()) bad = 1;
    }
    if(bad){
        cout<<-1<<endl;
    } 
    else {
        for(auto x : res) cout<<x<<" ";
        cout<<endl;
    }
}
int main() 
{
    
    return 0;
}
 