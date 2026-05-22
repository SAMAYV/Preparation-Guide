#include <bits/stdc++.h>
using namespace std;

bool isInsideMatrix(int row, int col, int n) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

int shortestPath(vector<vector<char>>& matrix, vector<vector<int>>& dist, pair<int, int> src, pair<int, int> dest) {
    int n = matrix.size();
    
    if (src == dest) return 0;
    
    map<char, pair<int, int>> nextStep;
    nextStep['>'] = {0, 1};
    nextStep['<'] = {0, -1};
    nextStep['v'] = {1, 0};
    nextStep['^'] = {-1, 0};
    
    int xa[4] = {1, -1, 0, 0};
    int ya[4] = {0, 0, 1, -1};
    
    // Dijkstra with priority queue: {cost, {row, col}}
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>, 
                   greater<pair<int, pair<int, int>>>> pq;
    
    pq.push({0, src});
    dist[src.first][src.second] = 0;
    
    while (!pq.empty()) {
        auto [cost, pos] = pq.top();
        pq.pop();
        
        int row = pos.first, col = pos.second;
        if (row == dest.first && col == dest.second) {
            return cost;
        }
        
        if (cost > dist[row][col]) continue;
        
        pair<int, int> step = nextStep[matrix[row][col]];
        
        for (int i = 0; i < 4; i++) {
            int newRow = row + xa[i];
            int newCol = col + ya[i];
            
            if (!isInsideMatrix(newRow, newCol, n)) continue;
            
            int edgeCost = (step.first == xa[i] && step.second == ya[i]) ? 0 : 1;
            int newCost = cost + edgeCost;
            
            if (newCost < dist[newRow][newCol]) {
                dist[newRow][newCol] = newCost;
                pq.push({newCost, {newRow, newCol}});
            }
        }
    }
    
    return dist[dest.first][dest.second];
}

int main() {
    int n;
    cin >> n;
    vector<vector<char>> matrix(n, vector<char>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    pair<int, int> src, dest;
    cin >> src.first >> src.second >> dest.first >> dest.second;
    
    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    int result = shortestPath(matrix, dist, src, dest);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << result << endl;
    return 0;
}