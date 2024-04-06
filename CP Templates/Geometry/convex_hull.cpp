struct pt {
    long double x, y;
};

bool compare(pt a, pt b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c){
    return a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c){
    return a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y) > 0;
}

vector<pt> convex_hull(vector<pt>& a){
    ll n = a.size();
    if(n == 1){
        return;
    }
    sort(a.begin(),a.end(),compare);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    REP(i,1,n){
        if(i == n - 1 || cw(p1, a[i], p2)){
            while(up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i])){
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if(i == n - 1 || ccw(p1, a[i], p2)){
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i])){
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }
    vector<pt> ans;
    REP(i,0,up.size()){
        ans.push_back(up[i]);
    }
    REPI(i,1,down.size()-1){
        ans.push_back(down[i]);
    }
    return ans;
}