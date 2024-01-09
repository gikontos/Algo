#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to, capacity, cost, flow;
    Edge(int t, int c, int cst, int f) : to(t), capacity(c), cost(cst), flow(f) {}
};

struct Graph {
    int V; // Number of vertices
    vector<vector<Edge>> adj;

    Graph(int V) : V(V), adj(V) {}

    void addEdge(int from, int to, int capacity, int cost) {
        Edge e1(to, capacity, cost, 0);
        Edge e2(from, 0, -cost, 0);
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
};

bool dijkstra(Graph& G, int source, vector<int>& distance) {
    distance.assign(G.V, numeric_limits<int>::max());
    vector<bool> visited(G.V, false);
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G.adj[u]) {
            int v = e.to;
            int w = e.cost;
            if (e.capacity - e.flow > 0 && distance[v] > distance[u] + w) {
                distance[v] = distance[u] + w;
                pq.push({distance[v], v});
            }
        }
    }

    return distance[G.V - 1] != numeric_limits<int>::max();
}

int minCostFlow(Graph& G, int source) {
    vector<int> distance(G.V);
    int minCost = 0;

    while (dijkstra(G, source, distance)) {
        int flow = numeric_limits<int>::max();

        // Calculate max possible flow along the path
        for (int v = G.V - 1; v != source; v = G.adj[v][0].to) {
            flow = min(flow, G.adj[v][0].capacity - G.adj[v][0].flow);
        }

        // Update flow and cost
        for (int v = G.V - 1; v != source; v = G.adj[v][0].to) {
            G.adj[v][0].flow += flow;
            G.adj[G.adj[v][0].to][0].flow -= flow;
            minCost += flow * G.adj[v][0].cost;
        }
    }

    return minCost;
}

int main() {
    int N; // Number of cities
    cin >> N;

    Graph G(N);

    // Reading paths and distances between cities
    for (int i = 1; i < N; ++i) {
        int from, to, distance;
        cin >> from >> to >> distance;
        G.addEdge(from, to, numeric_limits<int>::max(), distance);  // Add edge from 'from' to 'to' with given distance as cost
    }

    // Reading loading time and travel time for each city
    vector<pair<int, int>> sleigh_info(N); // Pi and Si for each city
    for (int i = 1; i < N; ++i) {
        int loading_time, travel_time;
        cin >> loading_time >> travel_time;
        sleigh_info[i] = make_pair(loading_time, travel_time);
    }

    int source = 0; // Assuming capital city is at index 0
    int target = 1; // Set your target city index

    // Add edges from source to cities and between cities as per the given sleigh information
    for (int i = 1; i < N; ++i) {
        G.addEdge(source, i, sleigh_info[i].first, 0); // Add edge from source to each city with loading time as capacity and 0 cost
        G.addEdge(i, target, numeric_limits<int>::max(),sleigh_info[i].second); // Add edge from each city to the target with capacity and travel time as cost
    }

    int minTime = minCostFlow(G, source);
    cout << "Minimum time for each city's letters to reach the capital: " << minTime << " seconds\n";

    return 0;
}


