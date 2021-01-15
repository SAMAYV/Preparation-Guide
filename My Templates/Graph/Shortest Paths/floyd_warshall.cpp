void floydWarshall(vector<vector<ll>> graph,ll n)  
{  
    ll dist[n][n];  
    REP(i,0,n){
        REP(j,0,n){
            dist[i][j] = graph[i][j];
        }
    }  
              
    REP(k,0,n){  
        REP(i,0,n){  
            REP(j,0,n){  
                if(dist[i][k] < 1e18 && dist[k][j] < 1e18 && dist[i][k] + dist[k][j] < dist[i][j])  
                    dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }   
    REP(i,0,n){
        REP(j,0,n){
            REP(t,0,n){
                if(dist[i][t] < 1e18 && dist[t][t] < 0 && dist[t][j] < 1e18)
                    dist[i][j] = -1e18; 
            }
        }
    }
}   
// A shortest path between vertices i and j does not exist, if and only if, there is a vertex t that is reachable from i and also from j, for which d[t][t] < 0.
