#pragma GCC optimize("O3")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using base = complex<double>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define M 1000000007
#define M2 998244353
#define ll long long
#define pll pair<long, long>
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define ff first
#define ss second
#define pb push_back
#define db pop_back
#define mp make_pair
#define mt make_tuple
#define g(a, b) get<a>(b)
#define INF (ll)1e18 + 100
#define vl vector<ll>
#define vi vector<int>
#define vll vector<pair<ll, ll>>
#define vii vector<pair<int, int>>
#define all(v) v.begin(), v.end()
#define bset(a, p) ((a) | (1ll << (p)))
#define bchk(a, p) ((a) & (1ll << (p)))
#define bxor(a, p) ((a) ^ (1ll << (p)));
#define brem(a, p) (bchk(a, p) ? (bxor(a, p)) : (a))
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
 
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
 
ll modI(ll a, ll m);
ll gcd(ll a, ll b);
ll powM(ll x, unsigned ll y, unsigned ll m);
void pairsort(int a[], int b[], int n);
void pairsortll(ll a[], ll b[], ll n);
ll logint(ll x, ll y);
 
ll gcd(ll x, ll y)
{
    if (x == 0)
        return y;
    return gcd(y % x, x);
}
 
ll powM(ll x, ll y, ll m)
{
    if (y == 0)
        return 1;
    ll p = powM(x, y / 2, m) % m;
    p = (p * p) % m;
    return (y % 2 == 0) ? p : (x * p) % m;
}
 
/*ll modI(ll a, ll m)
{
   return powM(a, m-2, m);
}*/
ll modI(ll a, ll m)
{
    ll m0 = m, y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1)
    {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}
void pairsort(int a[], int b[], int n)
{
    pair<int, int> v[n];
    REP(i, 0, n)
    {
        v[i].ff = a[i];
        v[i].ss = b[i];
    }
    sort(v, v + n);
    REP(i, 0, n)
    {
        a[i] = v[i].ff;
        b[i] = v[i].ss;
    }
}
 
void pairsortll(ll a[], ll b[], ll n)
{
    pair<ll, ll> v[n];
    REP(i, 0, n)
    {
        v[i].ff = a[i];
        v[i].ss = b[i];
    }
    sort(v, v + n);
    REP(i, 0, n)
    {
        a[i] = v[i].ff;
        b[i] = v[i].ss;
    }
}
 
ll logint(ll x, ll y)
{
    ll ans = 0;
    ll a = 1;
    for (ll i = 0; i <= x; i++)
    {
        if (x < a)
        {
            return ans;
        }
        ans++;
        a *= y;
    }
    return -1;
}
/*const int N = 1e6+5;
int parent[N];
int siz[N];
void make(){
    REP(i, 0, N){
        parent[i]=i;
        siz[i] = 1;
    }
}
int find(int x){
    while(parent[x] != x){
        x = parent[x];
    }
    return x;
}
void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(a != b){
        if(siz[a] < siz[b]){
            swap(a, b);}
        parent[b] = a;
        if(siz[a] == siz[b]){
            siz[a]++;
        }
    }
}*/
/*pair<ll, string> hashtable[100005];
int hashfunc(ll x){
    return x%100001;
}
string search(ll x){
    int j = hashfunc(x);
    while(hashtable[j].ff != x && hashtable[j].ss != ""){
        j = (j+1)%100001;
    }
    return hashtable[j].ss;
}
 
void insert(ll x, string s){
    int j = hashfunc(x);
    while(hashtable[j].ss != ""){
        j = (j+1)%100001;
    }
    hashtable[j].ff = x;
    hashtable[j].ss = s;
}*/
 
ll extended(ll a, ll b, ll &x, ll &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = extended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
ll lcm(ll x, ll y)
{
    return (x * y) / __gcd(x, y);
}
/*const ll N = 60;
struct trienode{
    ll val=0;
    struct trienode* ar[2];
};
struct trienode *newNode() 
{ 
    struct trienode *temp = new struct trienode; 
    temp->val = 0; 
    temp->ar[0] = temp->ar[1] = NULL; 
    return temp; 
} 
void insert(struct trienode* root, ll prexor){
    struct trienode* node = root;
    for(ll i=N; i>=0; i--){
        if((prexor&(1<<i))){
            if(node->ar[1]){
                node = node->ar[1];
            }
            else{
                node->ar[1] = newNode();
                node = node->ar[1];
            }
        }
        else{
            if(node->ar[0]){
                node = node->ar[0];
            }
            else{
                node->ar[0] = newNode();
                node = node->ar[0];
            }
        }
    }
    node->val = prexor;
}
ll query(struct trienode* root, ll prexor){
    struct trienode* node = root;
    for(ll i= N; i>=0; i--){
        //if(i == 0){return prexor^(node->val);}
        bool a = (prexor&(1<<i));
        if(node->ar[1-a]){
            node = node->ar[1-a];
        }
        else if(node->ar[a]){
            node = node->ar[a];
        }
    }
    return (prexor^(node->val));
}
*/
/*void solve(ll n, ll a, ll b){
    if(6*n < a){cout<<fixed<<setprecision(6)<<0.0;}
    else if(n > b){cout<<fixed<<setprecision(6)<<0.0;}
    else{
        double dp[6*n+7];
        REP(i,0,6*n+7){
            dp[i] = 0;
        }
        dp[0]=1;
        double sum = 0;
        REP(i,0,n){
            for(ll j=6*i; j>= i; j--){
                for(ll k=6; k>=1; k--){
                    dp[j+k]+=dp[j];
                }
            }
        }
        double ans = sum;
        REP(i,0,n){
            ans /= 6.0;
        }
        cout<<fixed<<setprecision(6)<<ans;
    }
}*/
/*ll solve(string s)
{
    ll n = s.size();
    vector<ll> d1(n);
    ll sum1 = 0, sum2=0;
    for (ll i = 0, l = 0, r = -1; i < n; i++)
    {
        ll k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
        sum1+=d1[i];
    }
    vector<ll> d2(n);
    for (ll i = 0, l = 0, r = -1; i < n; i++)
    {
        ll k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        d2[i] = k--;
        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k;
        }
        sum2+=d2[i];
    }
    return abs(sum1-sum2);
}*/
// const int N  = 2e5+5;
// int ar[26][N];
/*const int N = 5005;
vl v(N);
vl c(N);
ll n;
int dp[N][N][2];
void solve(int l, int r){
    if(dp[l][r][0] != INT_MAX && dp[l][r][1] != INT_MAX){return ;}
    if(l == r){
        dp[l][r][0]=dp[l][r][1]=0;
        return;
    }
    solve(l+1,r);
    solve(l,r-1);
    if(c[l] == c[l+1]){
        dp[l][r][0] = min(dp[l+1][r][0], dp[l][r][0]);
    }
    else{
        dp[l][r][0] = min(dp[l+1][r][0]+1, dp[l][r][0]);
    }
 
    if(c[l] == c[r]){
        dp[l][r][0] = min(dp[l][r][0], dp[l+1][r][1]);
    }
    else{
        dp[l][r][0] = min(dp[l][r][0], dp[l+1][r][1]+1);
    }
 
    if(c[r] == c[r-1]){
        dp[l][r][1] = min(dp[l][r-1][1], dp[l][r][1]);
    }
    else{
        dp[l][r][1] = min(dp[l][r-1][1]+1, dp[l][r][1]);
    }
 
    if(c[l] == c[r]){
        dp[l][r][1] = min(dp[l][r][1], dp[l][r-1][0]);
    }
    else{
        dp[l][r][1] = min(dp[l][r][1], dp[l][r-1][0]+1);
    }
 
}*/
 
/*const double PI = 4*atan(1);
const ll N=2e5+5;
const ll MOD=13313;
ll p;
ll FFT_N=0;
vector<base> omega;
 
void init_fft(ll n)
{
	FFT_N = n;
	omega.resize(n);
	double angle = 2*PI/n;
	for(int i=0;i<n;i++)
	{
		omega[i]=base(cos(i*angle), sin(i*angle));
	}
}
 
void fft(vector<base> &a)
{
	ll n=a.size();
	if(n==1)
		return;
	ll half=n>>1;
	vector<base> even(half), odd(half);
	for(ll i=0, j=0; i<n; i+=2, j++)
	{
		even[j]=a[i];
		odd[j]=a[i+1];
	}
	fft(even);
	fft(odd);
	ll denominator=FFT_N/n;
	for(ll i=0;i<half;i++)
	{
		base cur=odd[i] * omega[i*denominator];
		a[i]=even[i] + cur;
		a[i+half]=even[i] - cur;
	}
}
 
void multiply(vector<ll> &a, vector<ll> &b, vector<ll> &res)
{
	vector<base> fa(a.begin(), a.end());
	vector<base> fb(b.begin(), b.end());
	ll n=1;
	while(n<2*max(a.size(), b.size()))
		n<<=1;
	fa.resize(n);
	fb.resize(n);
	init_fft(n);
	fft(fa);
	fft(fb);
	for(ll i=0;i<n;i++)
		fa[i] = conj(fa[i] *  fb[i]);
	fft(fa);
	res.resize(n);
	for(ll i=0;i<n;i++)
	{
		res[i]=(long long)(fa[i].real()/n + 0.5);
		res[i]%=p;
        if(res[i]){cout<<i; return;}
	}
}*/

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //clock_t begin = clock();
    // clock_t start;
    // double duration;
 
    // start = std::clock();
    
    // duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
 
    // std::cout<<"printf: "<< duration <<'\n';
}