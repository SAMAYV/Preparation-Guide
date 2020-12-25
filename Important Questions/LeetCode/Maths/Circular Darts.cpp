#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long 
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set1;
typedef tree<string,null_type,less<string>,rb_tree_tag,tree_order_statistics_node_update> indexed_set2;
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

// https://leetcode.com/contest/weekly-contest-189/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/

/*
You have a very large square wall and a circular dartboard placed on the wall. You have been challenged to throw darts into the board blindfolded. Darts thrown at the wall are represented as an array of points on a 2D plane. 

Return the maximum number of points that are within or lie on any circular dartboard of radius r.

    1 <= points.length <= 100
    points[i].length == 2
    -10^4 <= points[i][0], points[i][1] <= 10^4
    1 <= r <= 5000

*/
class Solution {
public:
    const double tol = 1e-6;
    double R;

    struct Point {
        double x, y;
    };
    
    vector<Point> point;
    
    double dis(const Point& a, const Point& b) {
        return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    }

	pair<Point, Point> getCenter(const Point& a, const Point& b) {
		Point mid;
		pair<Point, Point> res;
		mid.x = (a.x + b.x) / 2, mid.y = (a.y + b.y) / 2;
		double theta = atan2(a.y - b.y, b.x - a.x);
		double tmp = dis(a, b) / 2;
		double d = sqrt(R * R - tmp*tmp);
		res.first.x = mid.x - d*sin(theta);
		res.first.y = mid.y - d*cos(theta);
		res.second.x = mid.x + d*sin(theta);
		res.second.y = mid.y + d*cos(theta);
		return res;
	}

	int numPoints(vector<vector<int>>& points, int r) {
		int n = points.size();
		R = (double)r;
		point.resize(n);
		for (int i = 0; i < n; ++i) {
			point[i].x = points[i][0];
			point[i].y = points[i][1];
		}
		int ans = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j || dis(point[i], point[j]) - 2 * R > tol) continue;
				int cnt = 0;
				auto p = getCenter(point[i], point[j]);
				for (int k = 0; k<n; k++) {
					if (dis(point[k], p.first) - R <= tol) 
						cnt++;
				}
				ans = max(ans, cnt);
				cnt = 0;
				for (int k = 0; k<n; k++) {
					if (dis(point[k], p.second) - R <= tol) 
						cnt++;
				}
				ans = max(ans, cnt);
			}
		}
		return ans;
	}
};

int main()
{
	
	return 0;
}
