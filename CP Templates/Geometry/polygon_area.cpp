// Pick’s theorem provides another way to calculate the area of a polygon provided that all vertices of the polygon have integer 
// coordinates. According to Pick’s theorem, the area of the polygon is a + b/2 - 1, where a is the number of integer points inside 
// the polygon and b is the number of integer points on the boundary of the polygon.

class Point {
    public:
    ld x,y;
};
class Polygon {
    public:
    Point* points;
    Polygon(ll n){
        points = new Point[n];
    }
};
ld Area(Polygon p,ll n){
    ld area = 0;
    REP(i,1,n-1){
        ld x1 = p.points[i].x - p.points[0].x;
        ld y1 = p.points[i].y - p.points[0].y;
        ld x2 = p.points[i+1].x - p.points[0].x;
        ld y2 = p.points[i+1].y - p.points[0].y;
        area += x1*y2 - x2*y1;
    }
    return abs(area)/2;
}
int main() 
{
	ll n;
    cin>>n;
    Polygon p(n);
    REP(i,0,n){
        cin>>p.points[i].x>>p.points[i].y;
    }
    cout<<Area(p,n)<<endl;
}