struct pt {
    ld x, y;
    pt operator-(pt p){
        pt res = {x-p.x,y-p.y};
        return res;
    }
};

struct circle: pt {
    ld r;
};

struct line {
    ld a, b, c;
};

ld sqr(ld a){
    return a*a;
}

void tangents(pt v,ld r1,ld r2,vector<line>& ans){
    ld r = r2 - r1;
    ld z = sqr(v.x) + sqr(v.y);
    ld d = z - sqr(r);

    // one circle is inside other circle and no tangent is found
    if(d < -1e-9){
    	return;	
    }  
    d = sqrt(abs(d));
    line l;
    l.a = (v.x * r + v.y * d) / z;
    l.b = (v.y * r - v.x * d) / z;
    l.c = r1;
    ans.push_back(l);
}

vector<line> tangents(circle a, circle b){
    // contains all the tangent lines
    vector<line> ans;
    for(ll i = -1; i <= 1; i += 2){
        for(ll j = -1; j <= 1; j += 2){
        	// making circle a center as (0,0)
            tangents(b-a, a.r*i, b.r*j, ans);
        }
    }
    for(size_t i = 0; i < ans.size(); ++i){
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
    }
    return ans;
}