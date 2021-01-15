long double sqrt_newton(long double n){
    const double eps = 1E-15;
    long double x = 1;
    for(;;){
        long double nx = (x + n / x) / 2;
        if (abs(x - nx) < eps)
            break;
        x = nx;
    }
    return x;
}

ll isqrt_newton(ll n){
    ll x = 1;
    REPI(i,0,60){
    	if((n >> i) & 1){
    		x = (1LL << (i/2));
    		break;
    	}
    }
    bool decreased = false;
    for(;;){
        ll nx = (x + n / x) >> 1LL;
        if(x == nx || nx > x && decreased)
            break;
        decreased = nx < x;
        x = nx;
    }
    return x;
}

// It is not difficult to obtain the following formula: x(i+1) = x(i) − f(x(i))/f′(x(i))