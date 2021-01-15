namespace fft {
  const double pi = acos(-1.0);
  struct Complex 
  {
    double r, i;
    Complex(double x = 0, double y = 0) : r(x), i(y) {}
    Complex operator+ (const Complex& b) const {
      return Complex(r + b.r, i + b.i);
    }
    Complex operator- (const Complex& b) const {
      return Complex(r - b.r, i - b.i);
    }
    Complex operator* (const Complex& b) const {
      return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
  };
  
  Complex conj(Complex a) { 
    return Complex(a.r, -a.i); 
  }
 
  int base = 1;
  vector<int> rev = { 0, 1 };
  vector<Complex> roots = { { 0, 0 }, { 1, 0 } };
  
  void ensure_base(int nbase) 
  {
    if(nbase <= base) return;
    rev.resize(1 << nbase);
    for(int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    roots.resize(1 << nbase);
    while(base < nbase){
      double angle = 2 * pi / (1 << (base + 1));
      for (int i = 1 << (base - 1); i < (1 << base); i++) {
        roots[i << 1] = roots[i];
        double angle_i = angle * (2 * i + 1 - (1 << base));
        roots[(i << 1) + 1] = Complex(cos(angle_i), sin(angle_i));
      }
      base++;
    }
  }
  void fft(vector<Complex> &a, int n = -1) {
    if (n == -1) {
      n = a.size();
    }
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++) {
      if (i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for (int k = 1; k < n; k <<= 1) {
      for (int i = 0; i < n; i += 2 * k) {
        for (int j = 0; j < k; j++) {
          Complex z = a[i + j + k] * roots[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
  }
 
  vector<Complex> fa, fb;
  vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    int need = a.size() + b.size() - 1;
    int nbase = need > 1 ? 32 - __builtin_clz(need - 1) : 0;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int) fa.size()) {
      fa.resize(sz);
    }
    for (int i = 0; i < sz; i++) {
      int x = (i < (int) a.size() ? a[i] : 0);
      int y = (i < (int) b.size() ? b[i] : 0);
      fa[i] = Complex(x, y);
    }
    fft(fa, sz);
    Complex r(0, -0.25 / sz);
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      Complex z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
      if (i != j) {
        fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
      }
      fa[i] = z;
    }
    fft(fa, sz);
    vector<int> res(need);
    for (int i = 0; i < need; i++) {
      res[i] = fa[i].r + 0.5; // watch out that fa[i].r < 0
    }
    return res;
  }
  
}
 
int main() 
{
    // aa and bb vectors will contain coeficients of ith powers of x. Indexing into the vector will tell coefficient of x^i.
    vector<int> c = fft::multiply(aa, bb);
    return 0; 
}
 