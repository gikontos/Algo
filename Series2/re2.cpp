#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

typedef pair<int, double> pid; // (time, node)
typedef unordered_map<int, unordered_map<int, int>> AdjList; // Adjacency List: node -> {neighbor -> distance}

unordered_map<int, double> min_time_to_target(int root, vector<double>& pi, vector<double>& si, AdjList& di) {
    unordered_map<int, double> min_time;
    min_time[root] = 0.0;

    priority_queue<pid, vector<pid>, greater<pid>> pq;
    pq.push({0, root});

    while (!pq.empty()) {
        double cur_time = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (const auto& neighbor : di[node]) {
            int next_node = neighbor.first;
            int distance = neighbor.second;

            double time_to_neighbor = cur_time + pi[node] + static_cast<double>(distance) / si[node];

            if (min_time.find(next_node) == min_time.end() || time_to_neighbor < min_time[next_node]) {
                min_time[next_node] = time_to_neighbor;
                pq.push({time_to_neighbor, next_node});
            }
        }
    }

    return min_time;
}

int main() {
    int n;
    cin >> n;

    // Initialize vectors to store pi and si values for each node
    vector<double> p(n + 1), s(n + 1);

    // Initialize adjacency list to store the graph
    AdjList di;

    // Read edge information and distances
    for (int i = 0; i < n-1; ++i) {
        int v, vj, d;
        cin >> v >> vj >> d;

        // Add edge and distance to adjacency list
        di[v][vj] = d;
        di[vj][v] = d;
    }

    // Read pi values
    for (int i = 1; i < n; ++i) {
        cin >> p[i] >> s[i];
    }

    int root = 1; // Change this to your target node

    unordered_map<int, double> result = min_time_to_target(root, p, s, di);

    cout << "Minimum time to reach target node from each node:\n";
    for (const auto& entry : result) {
        cout << "Node " << entry.first << ": " << entry.second << " units of time\n";
    }

    return 0;
}
