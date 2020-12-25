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

int main()
{
    ll n,k,p;
    cin>>n>>k>>p;
    ll arr[n];
    REP(i,0,n){
        cin>>arr[i];
    }
    ll l = 1,u = 1e10;
    ll ans = 0;
    while(l <= u){
        ll mid = (l + u)/2;
        ll temp[n];
        REP(i,0,n){
            temp[i] = max(0LL,mid - arr[i]);
        }
        ll i = 0, ct = 0, prev = 0, temp_ans = 0, temp1 = 0;
        while(i < n){
            if(temp[i] > prev){
                temp_ans += temp[i] - temp1;
                temp1 = temp[i] - temp1;
                ct = 0;
                prev = temp[i];
            }
            if(prev > 0){
                ct++;
            }
            if(ct >= k){
                ct = 0;
                prev = 0;
                temp1 = 0;
            }
            i++;
        }
        if(temp_ans <= p){
            ans = max(ans,mid);
            l = mid + 1;
        }
        else {
            u = mid - 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}