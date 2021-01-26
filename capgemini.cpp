typedef long long ll;
typedef pair<int, int> ii;
const int inf = 1e9 + 143;
const ll longinf = 1e18 + 143;
const int N = 20001;

inline int read()
{

    int x;
    scanf(" %d",&x);
    return x;
}

int n;
int a[N];
void read_inp()
{
    n = read();
    assert(1 <= n && n <= 20000);
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
        assert(abs(a[i]) <= int(1e6));
    }
}

int main()
{
    read_inp();
    ll ans = -longinf;
    for(int i = 1; i <= n; i++)
    {
        int l = i - 1, r = i;
        ll best = 0ll, cur = 0ll;
        while(l >= 1 && r <= n)
        {
            ll val = (ll)a[l] * a[r];
            cur += val;
            if(best > cur) best = cur;
            if(ans < cur - best) ans = cur - best;
            --l;
            ++r;
        }
        
        l = i - 1; 
        r = i + 1;
        best = 0ll; 
        cur = 0ll;
        while(l >= 1 && r <= n)
        {
           ll val = (ll)a[l] * a[r];
           cur += val;
           if(best > cur) best = cur;
           if(ans < cur - best) ans = cur - best;
           --l;
           ++r;
        }
    }
    printf("%lld\n",ans);
    return 0;
}