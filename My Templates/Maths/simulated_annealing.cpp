// https://leetcode.com/contest/weekly-contest-197/problems/best-position-for-a-service-centre/

/*
A delivery company wants to build a new service centre in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new centre in a position such that the sum of the euclidean distances to all customers is minimum.

Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.

In other words, you need to choose the position of the service centre [xcentre, ycentre] such that the following formula is minimized:

Answers within 10^-5 of the actual value will be accepted.

*/

class Solution {
    double dist(vector<int> &a, vector<double> &b) {
        return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
    }
    double all(vector<vector<int>> &A, vector<double> &p) {
        double ans = 0;
        for (auto &a : A) ans += dist(a, p);
        return ans;
    }
    const int dirs[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
    
	public:
    double getMinDistSum(vector<vector<int>>& A) {
        double ans = DBL_MAX;
        vector<double> p(2, 0);
        double step = 100, eps = 1e-6;
        while (step > eps) {
            bool found = false;
            for (auto &dir : dirs) {
                vector<double> next = {p[0] + step * dir[0], p[1] + step * dir[1]};
                double d = all(A, next);
                if (d < ans) {
                    ans = d;
                    p = next;
                    found = true;
                    break;
                }
            }
            if (!found) step /= 2;
        }
        return ans;
    }
};
