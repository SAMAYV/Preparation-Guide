using cd = complex<long double>;
const long double PI = acos(-1);
 
void fft(vector<cd>& a,bool invert) 
{
    ll n = a.size();
    for(ll i = 1, j = 0; i < n; i++){
        ll bit = n >> 1;
        for(; j & bit; bit >>= 1){
            j ^= bit;
        }
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }
    for(ll len = 2; len <= n; len <<= 1){
        long double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(ll i = 0; i < n; i += len){
            cd w(1);
            for(ll j = 0; j < len / 2; j++){
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if(invert){
        for(cd& x : a)
            x /= n;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while(n < a.size() + b.size()){
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for(ll i = 0; i < n; i++){
        fa[i] *= fb[i];
    }
    fft(fa, true);
 
    vector<ll> result(n);
    for(ll i = 0; i < n; i++){
        result[i] = round(fa[i].real());
    }
    return result;
}
 
int main() 
{
    // aa and bb vectors will contain coeficients of ith powers of x. Indexing into the vector will tell coefficien of x^i.
    vector<int> c = fft::multiply(aa, bb);
    return 0; 
}
 