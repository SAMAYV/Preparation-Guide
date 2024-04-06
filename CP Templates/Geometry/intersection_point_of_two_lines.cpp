// You are given two lines, described via the equations a1x+b1y+c1=0 and a2x+b2y+c2=0. 
// We have to find the intersection point of the lines, or determine that the lines are parallel.

struct pt {
    ld x, y;
};
struct line {
    ld a, b, c;
};

ld det(ld a,ld b,ld c,ld d){
    return a*d - b*c;
}
bool intersect(line m,line n,pt& res){
    ld zn = det(m.a, m.b, n.a, n.b);
    if(abs(zn) < 1e-9){
        return false;
    }
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}
bool parallel(line m,line n){
    return abs(det(m.a, m.b, n.a, n.b)) < 1e-9;
}
bool equivalent(line m,line n){
    return abs(det(m.a, m.b, n.a, n.b)) < 1e-9 && abs(det(m.a, m.c, n.a, n.c)) < 1e-9 && abs(det(m.b, m.c, n.b, n.c)) < 1e-9;
}