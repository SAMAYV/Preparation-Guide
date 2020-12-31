// A useful technique related to Manhattan distances is to rotate all coordinates 45 degrees so that a point (x, y) becomes 
// (x + y, y - x) = (xnew,ynew). Now there are two ways to express the Manhattan distance between p1 and p2:
// |x1-x2| + |y1-y2| = max(|x1new - x2new|,|y1new - y2new|)

struct Point {
	ll x,ll y;
};

bool compare(Point a,Point b){
	return a.y < b.y;
}

ll max_manhattan_distance(vector<Point> points){
	ll n = points.size();
	REP(i,0,n){
		ll x1 = points[i].x; 
		ll y1 = points[i].y;
		points[i].x = x1 + y1;
		points[i].y = y1 - x1;
	}
	sort(points.begin(),points.end());
	ll maxi = 0;
	maxi = max(maxi,points[n-1].x - points[0].x);
	sort(points.begin(),points.end(),compare);
	maxi = max(maxi,points[n-1].y - points[0].y);
	return maxi;
}