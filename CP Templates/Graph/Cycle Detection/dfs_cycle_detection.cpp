bool dfs(int node, int par, vector<vector<int>>& adj,
         vector<int>& state, vector<int>& parent,
         vector<int>& cycle) {

    state[node] = 1;

    for (auto it : adj[node]) {
        if (it == par) continue;

        if (state[it] == 1) {
            // 🔥 Cycle found → reconstruct
            int curr = node;
            cycle.push_back(it);

            while (curr != it) {
                cycle.push_back(curr);
                curr = parent[curr];
            }

            cycle.push_back(it); // to complete cycle
            reverse(cycle.begin(), cycle.end());
            return true;
        }

        if (state[it] == 0) {
            parent[it] = node;
            if (dfs(it, node, adj, state, parent, cycle))
                return true;
        }
    }

    state[node] = 2;
    return false;
}

void findCycle(int n, vector<vector<int>>& adj) {
    vector<int> state(n, 0), parent(n, -1), cycle;

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfs(i, -1, adj, state, parent, cycle)) {
                cout << "Cycle found:\n";
                for (auto x : cycle) cout << x << " ";
                cout << endl;
                return;
            }
        }
    }

    cout << "No cycle\n";
}
