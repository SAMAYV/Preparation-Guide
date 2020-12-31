// Here ftype is some type used for coordinates, usually int, double or long long

typedef ftype long long

struct point2d 
{
    ftype x, y;
    point2d(){}
    point2d(ftype x, ftype y): x(x), y(y){}
    point2d& operator+=(const point2d &t){
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t){
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t){
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t){
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const{
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const{
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const{
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const{
        return point2d(*this) /= t;
    }
};
point2d operator*(ftype a, point2d b){
    return b * a;
}
ftype dot(point2d a, point2d b){
    return a.x * b.x + a.y * b.y;
}
ftype norm(point2d a){
    return dot(a, a);
}
double abs(point2d a){
    return sqrt(norm(a));
}
double proj(point2d a, point2d b){
    return dot(a, b) / abs(b);
}
double angle(point2d a, point2d b){
    return acos(dot(a, b) / abs(a) / abs(b));
}
ftype cross(point2d a, point2d b){
    return a.x * b.y - a.y * b.x;
}
// For example we have two lines and we want to find their intersection points. We can say that all points 
// from first line can be parameterized as r = a1 + t*d1 where a1 is initial point, d1 is direction and t is some real parameter. 
// As for second line all its points must satisfy (r − a2) × d2 = 0. From this we can easily find parameter t:
point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2){
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
ll signed_area_parallelogram(point2d p1, point2d p2, point2d p3){
    return cross(p2 - p1, p3 - p2);
}
double triangle_area(point2d p1, point2d p2, point2d p3){
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}
bool clockwise(point2d p1, point2d p2, point2d p3){
    return signed_area_parallelogram(p1, p2, p3) < 0;
}
bool counter_clockwise(point2d p1, point2d p2, point2d p3){
    return signed_area_parallelogram(p1, p2, p3) > 0;
}


struct point3d 
{
    ftype x, y, z;
    point3d(){}
    point3d(ftype x, ftype y, ftype z): x(x), y(y), z(z){}
    point3d& operator+=(const point3d &t){
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d& operator-=(const point3d &t){
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d& operator*=(ftype t){
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d& operator/=(ftype t){
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const{
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const{
        return point3d(*this) -= t;
    }
    point3d operator*(ftype t) const{
        return point3d(*this) *= t;
    }
    point3d operator/(ftype t) const{
        return point3d(*this) /= t;
    }
};
point3d operator*(ftype a, point3d b){
    return b * a;
}
ftype dot(point3d a, point3d b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
point3d cross(point3d a, point3d b){
    return point3d(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}
ftype triple(point3d a, point3d b, point3d c){
    return dot(a, cross(b, c));
}
// For example, you're given three planes defined by initial points ai and directions di and you want to find their intersection point
point3d intersect(point3d a1, point3d n1, point3d a2, point3d n2, point3d a3, point3d n3){
    point3d x(n1.x, n2.x, n3.x);
    point3d y(n1.y, n2.y, n3.y);
    point3d z(n1.z, n2.z, n3.z); 
    point3d d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point3d(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}