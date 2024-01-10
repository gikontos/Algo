#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge{
    int u, v;
    long cost;
    Edge(int k, int l, long m){
        u = k;
        v = l;
        cost = m;
    } 
};

struct City{
    vector<pair<int,long>> parents;//the parents and the distance to them
    long distance;//distance to capital
    int speed;
    int p;//the loading time
    City(){
        distance = 0;
    }
    City(const City& parent,int index,long d): parents(parent.parents){
        distance = parent.distance+d;
        for (auto& parentPair : parents) {
            parentPair.second += d;
        }
        pair<int,long> pair(index,d);
        parents.push_back(pair);
    }
};

vector<long long> dijkstra(vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<long long> distance(n, INF);
    distance[start] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        long long dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > distance[node]) continue;

        for (const Edge& edge : graph[node]) {
            if (distance[edge.v] > distance[node] + edge.cost) {
                distance[edge.v] = distance[node] + edge.cost;
                pq.push({distance[edge.v], edge.v});
            }
        }
    }

    return distance;
}

int main(){
    int n;
    cin >> n;
    vector<City> Cities(n+1);
    vector<vector<Edge>> graph(n+1);
    for(int i = 0; i<n-1; ++i){
        int u,v;
        long d;
        cin >> u >> v >> d;
        Cities[v] = City(Cities[u],u,d);
    }
    for(int i = 2; i<=n; ++i){
        long p, s;
        cin >> p >> s;
        Cities[i].p = p;
        Cities[i].speed = s;
    }
    for(int i = 2; i<=n; ++i){
        for(auto& parentPair : Cities[i].parents){
            long cost;
            cost = (parentPair.second*Cities[i].speed)+Cities[i].p;
            Edge e(parentPair.first,i,cost);
            graph[i].push_back(e);
            graph[parentPair.first].push_back(e);        
        }
    }

    vector<long long> minCosts = dijkstra(graph, 1);

    for (int i = 2; i < n; ++i) {
        cout << minCosts[i] << " ";
    }
    cout << minCosts[n];  
}