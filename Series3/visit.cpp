#include <iostream>
#include <vector>

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
// add comment
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
}