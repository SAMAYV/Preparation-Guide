#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

typedef ll ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a,point b){
    return (conj(a)*b).x();
}
ftype cross(point a,point b){
    return (conj(a)*b).y();
}

// kx + b. Lower convex hull is maintained for calculating minimum:
// Here we will assume that when linear functions are added, their k only increases and we want to find minimum values. 
// We will keep points in vector hull and normal vectors in vector vecs.
vector<point> hull, vecs;

void add_line(ftype k,ftype b){
    point nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0){
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()){
        vecs.push_back(1i*(nw - hull.back()));
    }
    hull.push_back(nw);
}

ll get(ftype x){
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b){
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}