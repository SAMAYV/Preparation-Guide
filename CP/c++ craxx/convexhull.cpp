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
#define forzm(i, m, n) for (int i = m; i < n; i++)
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
lli power(lli x, lli y, lli p)
{
    lli res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        //y must be even now
        y = y >> 1; //y=y/2
        x = (x * x) % p;
    }
    return res;
}
lli modi(lli a, lli m)
{
    // fermat little thm where m is prime
    return power(a, m - 2, m);
}
/*CODE BEGINS*/
bool cw(pair<lli, lli> a, pair<lli, lli> b, pair<lli, lli> c)
{
    return a.F * (b.S - c.S) + b.F * (c.S - a.S) + c.F * (a.S - b.S) < 0;
}
bool ccw(pair<lli, lli> a, pair<lli, lli> b, pair<lli, lli> c)
{
    return a.F * (b.S - c.S) + b.F * (c.S - a.S) + c.F * (a.S - b.S) > 0;
}
int main()
{
    kira;
    lli n;
    cin >> n;
    vector<pair<lli, lli>> v;
    lli x, y;
    forz(i, n)
    {
        cin >> x >> y;
        v.pb({x, y});
    }
    if (n == 1)
    {
        cout << v[0].F << " "<< v[0].S;
    }
    else
    {
        sort(all(v));
        vector<pair<lli, lli>> up, down;
        pair<lli, lli> p1 = v[0], p2 = v.back();
        up.pb(p1);
        down.pb(p1);
        if(p1==p2)
        {
            p1(1);
            p2(p1.F,p1.S);
            return 0;
        }
        for (int i = 1; i < v.si; i++)
        {
            if (i == v.si - 1 || cw(p1, v[i], p2))
            {
                while (up.si >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], v[i]))
                    up.pop_back();
                up.pb(v[i]);
            }
            if (i == v.si - 1 || ccw(p1, v[i], p2))
            {
                while (down.si >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], v[i]))
                    down.pop_back();
                down.pb(v[i]);
            }
        }
        v.clear();
        for(auto x:up)
            v.pb(x);
        for(int i=down.si-2;i>0;i--)
            v.pb(down[i]);
        p1(v.si);
        for(auto x:v)
        {
            p2(x.F,x.S);
        }
    }
    return 0;
}
