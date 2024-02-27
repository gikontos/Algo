#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge
{
    long u, v, d;
    Edge(long s, long t, long w)
    {
        u = s;
        v = t;
        d = w;
    }
};

vector<pair<Edge, long>> route(vector<vector<Edge>> adj, vector<long> &c)
{
    int time = 0;
    vector<pair<Edge, long>> president_route;
    for (size_t i = 0; i < c.size() - 1; ++i)
    {
        for (const Edge &edge : adj[c[i]])
        {
            if (c[i + 1] != edge.v)
            {
                ;
            }
            else
            {
                time = time + edge.d;
                auto pair = make_pair(edge, time);
                president_route.push_back(pair);
                break;
            }
        }
    }
    return president_route;
}

long checktime(long time, Edge edge, vector<pair<Edge, long>> route)
{
    long t = LONG_MAX;
    long w = edge.d;
    for (const auto &pair : route)
    {
        if ((pair.first.u == edge.u && pair.first.v == edge.v && pair.first.d == edge.d) || (pair.first.v == edge.u && pair.first.u == edge.v && pair.first.d == edge.d))
        {
            t = pair.second;
            break;
        }
    }
    if (time <= t - w - 1 || time >= t)
    {
        return w;
    }
    else
    {
        return (t - time + w);
    }
}

long dijkstra(long a, long b, long n, long t, vector<Edge> &g, vector<long> &c)
{
    vector<vector<Edge>> adj(n + 1);

    for (const Edge &edge : g)
    {
        adj[edge.u].push_back(edge);
        adj[edge.v].push_back({edge.v, edge.u, edge.d});
    }

    vector<long> dist(n + 1, LONG_MAX);
    vector<pair<Edge, long>> president_route = route(adj, c);
    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;

    pq.push(make_pair(0, a));
    dist[a] = 0;

    while (!pq.empty())
    {
        long u = pq.top().second;
        pq.pop();
        long time = t + dist[u];
        for (const Edge &edge : adj[u])
        {
            long v = edge.v;
            long weight = checktime(time, edge, president_route);
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return (dist[b] != LONG_MAX) ? dist[b] : -1;
}

int main()
{
    long n, m;
    cin >> n >> m;
    long a, b, t, k;
    cin >> a >> b >> t >> k;
    vector<long> c;
    for (int i = 0; i < k; ++i)
    {
        long j;
        cin >> j;
        c.push_back(j);
    }
    vector<Edge> g;
    for (int i = 0; i < m; ++i)
    {
        long s, t, w;
        cin >> s >> t >> w;
        Edge e(s, t, w);
        g.push_back(e);
    }
    long sol = dijkstra(a, b, n, t, g, c);
    cout << sol << '\n';
}