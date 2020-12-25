class Point {
    public:
        double x,y;
};
class Polygon {
    public:
    Point* points;
    Polygon(int n){
        points = new Point[n];
    }
};
double Area(Polygon p,int n){
    double area = 0;
    for(int i=1;i<n-1;i++){
        double x1 = p.points[i].x - p.points[0].x;
        double y1 = p.points[i].y - p.points[0].y;
        double x2 = p.points[i+1].x - p.points[0].x;
        double y2 = p.points[i+1].y - p.points[0].y;
        area += x1*y2 - x2*y1;
    }
    return abs(area)/2;
}
int main() {

	int n;
    cin>>n;
    Polygon p(n);
    for(int i=0;i<n;i++){
        cin>>p.points[i].x;
    }
    for(int i=0;i<n;i++){
        cin>>p.points[i].y;
    }
    cout<<(long)Area(p,n);
}