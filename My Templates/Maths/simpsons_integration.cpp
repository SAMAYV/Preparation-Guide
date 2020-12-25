 long double simpson_integration(long double a,long double b){
 	const ll N = 1000000LL;
    long double h = (b - a) / N;
    long double s = f(a) + f(b); // a = x_0 and b = x_2n
    REP(i,1,n){ 
        long double x = a + h*i;
        s += f(x)*((i & 1) ? 4LL : 2LL);
    }
    s *= h/3;
    return s;
}
// We are going to calculate the value of a definite integral a to b ∫f(x)dx.