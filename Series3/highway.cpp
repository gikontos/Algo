#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge
{
    int a, b, w;
    Edge(int s, int t, int g)
    {
        a = s;
        b = t;
        w = g;
    }
};

bool compare(Edge one, Edge two)
{
    return one.w > two.w;
}

class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 1);

        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootU] = rootV;
                rank[rootV]++;
            }
        }
    }

    void print()
    {
        cout << "DSU: ";
        for (int i = 1; i < parent.size(); ++i)
        {
            cout << find(i) << " ";
        }
        cout << endl;
    }
};

vector<Edge> Kruskal(vector<Edge> &edges, int N)
{
    sort(edges.begin(), edges.end(), compare);

    DSU dsu(N);
    vector<Edge> mst;

    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i].a;
        int v = edges[i].b;
        int w = edges[i].w;

        int set_u = dsu.find(u);
        int set_v = dsu.find(v);

        if (set_u != set_v)
        {
            dsu.unite(set_u, set_v);
            mst.push_back(edges[i]);
        }
    }
    return mst;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> g;
    for (int i = 0; i < m; ++i)
    {
        int a, b, t;
        cin >> a >> b >> t;
        Edge e(a, b, t);
        g.push_back(e);
    }
    vector<Edge> s = Kruskal(g, n);
    int p = s.size();
    if (p < k + 1)
    {
        cout << "infinity" << '\n';
    }
    else
    {
        cout << s[p - k - 1].w << '\n';
    }
}