/*print all elements in sorted order from row and column wise sorted matrix*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
struct values {
	int x,y,val;
};
struct compare{
	public:
	bool operator () (values const& a, values const& b) {
		return a.val > b.val;
	}
};
int main()
{
	int n;
	cin>>n;
	values mat[n][n];
	bool visited[n][n];
	REP(i,0,n){
		REP(j,0,n){
			cin>>mat[i][j].val;
			mat[i][j].x = i;
			mat[i][j].y = j;
			visited[i][j] = false;
		}
	}
	priority_queue<values,vector<values>,compare> pq;
	pq.push(mat[0][0]);
	visited[mat[0][0].x][mat[0][0].y];
	while(!pq.empty()){
		values v = pq.top();
		cout<<v.val<<" ";
		pq.pop();
		if(v.y < n-1 && visited[v.x][v.y + 1] == false){
			pq.push(mat[v.x][v.y + 1]);
			visited[v.x][v.y + 1] = true;
		}
		if(v.x < n-1 && visited[v.x + 1][v.y] == false){
			pq.push(mat[v.x + 1][v.y]);
			visited[v.x + 1][v.y] = true;
		}
	}
	return 0;
}