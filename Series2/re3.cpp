#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 100005; // Adjust this according to the constraints

vector<pair<int, int>> adj[MAX_NODES]; // Adjacency list to represent the tree
int loading_time[MAX_NODES]; // Loading time at each node
double carrier_speed; // Carrier speed

void dfs(int node, int parent, double current_time, vector<double>& min_time) {
    // Calculate time to reach current node based on carrier speed and distance
    current_time += (double)adj[parent][node].second / carrier_speed;

    // Calculate minimum time considering loading time at the current node
    min_time[node] = max(current_time, (double)loading_time[node]);

    // Traverse the children
    for (auto& child : adj[node]) {
        if (child.first != parent) {
            dfs(child.first, node, current_time, min_time);
        }
    }
}

int main() {
    int n;
    cin >> n;

    // Read edges and distances
    for (int i = 0; i < n - 1; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }

    // Read loading time and carrier speed for each node
    for (int i = 1; i < n; ++i) {
        cin >> loading_time[i] >> carrier_speed;
    }

    // Vector to store minimum time for each node
    vector<double> min_time(n);

    // Perform Depth-First Search (DFS) to calculate minimum time for each node
    dfs(1, 0, 0, min_time);

    // Output the minimum time for each node
    for (int i = 1; i <= n; ++i) {
        cout << "Minimum time for node " << i << ": " << min_time[i] << " units" << endl;
    }

    return 0;
}
