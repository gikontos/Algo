#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

void dijkstra(vector<vector<pair<int, int>>>& graph, vector<int>& times, int start) {
    int n = graph.size();
    times.assign(n, INF);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    times[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (times[v] > times[u] + weight) {
                times[v] = times[u] + weight;
                pq.push({times[v], v});
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<vector<pair<int, int>>> graph(N);
    vector<int> loadingTime(N), travelTime(N);

    for (int i = 0; i < N - 1; ++i) {
        int u, v, distance;
        cin >> u >> v >> distance;
        graph[u - 1].push_back({v - 1, distance});
        graph[v - 1].push_back({u - 1, distance});
    }

    for (int i = 0; i < N - 1; ++i) {
        int loading, travel;
        cin >> loading >> travel;
        loadingTime[i + 1] = loading;
        travelTime[i + 1] = travel;
    }

    vector<int> arrivalTimes;
    dijkstra(graph, arrivalTimes, 0);

    for (int i = 1; i < N; ++i) {
        int totalTime = loadingTime[i] + travelTime[i] * arrivalTimes[i];
        cout << totalTime << " ";
    }

    return 0;
}

