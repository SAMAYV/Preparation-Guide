// https://www.codechef.com/NOV17/problems/POLY
// https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

const ll N = 1e5 + 5;
const ll C = 1e5 + 5;
const ll T = 10;
const ll M = 350; // sqrt(10^5)
const ll inf = (ll)1e19;

struct Poly {
    ll a, b, c, d = inf;
    ll operator()(ll x){
      return a * x * x * x + b * x * x + c * x + d;
    }
} a[T][C * 4];

ll t = -1;

void insert(ll l,ll r,Poly poly,ll treenode = 1){
    if(l + 1 == r){
      if(poly(l) < a[t][treenode](l)) a[t][treenode] = poly;
      return;
    }
    ll mid = (l + r) >> 1;
    bool b1 = poly(mid) < a[t][treenode](mid), b2 = poly(l) < a[t][treenode](l);
    if(b1) swap(poly, a[t][treenode]);
    if(b1 != b2) insert(l, mid, poly, 2*treenode);
    else insert(mid, r, poly, 2*treenode + 1);
}

ll query(ll l,ll r,ll x,ll treenode = 1){
    if(l + 1 == r) return a[t][treenode](x);
    ll mid = (l + r) >> 1;
    if(x < mid) return min(a[t][treenode](x), query(l, mid, x, 2*treenode));
    else return min(a[t][treenode](x), query(mid, r, x, 2*treenode + 1));
}

ll ans[M];

void init(){
    ll n;
    cin >> n;
    fill(ans, ans + M, inf);
    t++;
    while(n--) {
        ll a, b, c, d;
        cin >> d >> c >> b >> a;
        Poly p = {a, b, c, d};
        insert(M, C, p);
        for(int i = 0; i < M; i++) ans[i] = min(ans[i], p(i));
    }
}

void solve(){
    ll q;
    cin >> q;
    while(q--){
        ll x;
        cin >> x;
        if(x < M) cout << ans[x] << '\n';
        else cout << query(M, C, x) << '\n';
    }
}

int main()
{
    ll t;
    cin >> t;
    while(t--){
        init();
        solve();
    }
    return 0;
}