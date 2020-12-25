ll gcd(ll a,ll b,ll& x,ll& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

//note that this code does not consider the case a=b=0
bool find_any_solution(ll a,ll b,ll c,ll& x0,ll& y0,ll& g){
    g = gcd(abs(a),abs(b),x0,y0);
    if(c % g){
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if(a < 0) x0 = -x0;
    if(b < 0) y0 = -y0;
    return true;
}

void shift_solution(ll& x,ll& y,ll a,ll b,ll cnt){
    x += cnt * b;
    y -= cnt * a;
}

// returns no of solutions in the range x: [minx,maxx], y: [miny,maxy]
ll find_all_solutions(ll a,ll b,ll c,ll minx,ll maxx,ll miny,ll maxy){
    ll x, y, g;
    if(!find_any_solution(a, b, c, x, y, g)){
        return 0;
    }
    a /= g;
    b /= g;

    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if(x < minx)
        shift_solution(x, y, a, b, sign_b);
    if(x > maxx)
        return 0;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if(x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if(y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if(y > maxy)
        return 0;
    ll lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if(y > maxy)
        shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;

    if(lx2 > rx2)
        swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);

    if(lx > rx){
        return 0;
    }
    return (rx - lx) / abs(b) + 1;
}

// Once we have lx and rx, it is also simple to enumerate through all the solutions. 
// Just need to iterate through x = lx + k⋅b/g for all k ≥ 0 until x = rx and find the corresponding y values using the equation ax + by = c.  
    