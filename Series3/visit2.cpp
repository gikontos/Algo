#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph
{
private:
    int n;                    // Αριθμός πόλεων
    vector<vector<int>> dist; // Πίνακας αποστάσεων

public:
    vector<int> presidentPath; // Πορεία του Προέδρου
    Graph(int vertices) : n(vertices)
    {
        // Αρχικοποίηση του πίνακα αποστάσεων
        dist.assign(n + 1, vector<int>(n + 1, INT_MAX));
    }

    void addEdge(int u, int v, int d)
    {
        // Προσθήκη ακμής στο γράφο
        dist[u][v] = d;
        dist[v][u] = d;
    }

    bool canUseRoad(int u, int v, int startTime, int endTime)
    {
        // Ελέγχος αν ο δρόμος είναι διαθέσιμος μετά την αναχώρηση του Προέδρου
        if (startTime > endTime)
        {
            return false;
        }

        if (!presidentPath.empty())
        {
            for (int i = 0; i < presidentPath.size() - 1; ++i)
            {
                int presidentRoadStartTime = dist[presidentPath[i]][presidentPath[i + 1]];
                int presidentRoadEndTime = presidentRoadStartTime + 1; // Υποθέτουμε ότι ο Πρόεδρος κάνει μόνο ένα βήμα ανά δρόμο
                if (startTime >= presidentRoadStartTime && endTime <= presidentRoadEndTime)
                {
                    return false;
                }
            }
        }

        return true;
    }

    int dijkstraWithPresident(int source, int destination, int startTime, vector<int> &route)
    {
        // Αρχικοποίηση πίνακα αποστάσεων
        vector<vector<int>> distWithTime(n + 1, vector<int>(n + 1, INT_MAX));

        // Προτεραιότητα με βάση τον χρόνο
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

        // Αρχικοποίηση του πρώτου κόμβου
        pq.push({0, {startTime, source}});
        distWithTime[source][startTime] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second.second;
            int currentDist = pq.top().first;
            int currentTime = pq.top().second.first;
            pq.pop();

            if (currentTime > distWithTime[u].size() - 1)
            {
                continue; // Αν ο χρόνος έχει υπερβεί τη διαθέσιμη διάρκεια για τον κόμβο u, προχωράμε στον επόμενο κόμβο
            }

            if (currentDist > distWithTime[u][currentTime])
            {
                continue; // Αν έχουμε βρει καλύτερο τρόπο να φτάσουμε στον κόμβο u με τον ίδιο χρόνο, προχωράμε στον επόμενο κόμβο
            }

            // Εξερεύνηση όλων των γειτόνων του u
            for (int v = 1; v <= n; ++v)
            {
                if (dist[u][v] != INT_MAX && canUseRoad(u, v, currentTime, currentTime + dist[u][v]))
                {
                    int newDist = currentDist + dist[u][v];
                    int newTime = currentTime + dist[u][v];

                    if (newTime < distWithTime[v].size() && newDist < distWithTime[v][newTime])
                    {
                        distWithTime[v][newTime] = newDist;
                        pq.push({newDist, {newTime, v}});
                    }
                }
            }
        }

        // Εύρεση βέλτιστης διαδρομής και επιστροφή του μήκους της
        int minDistance = INT_MAX;
        int endTime = distWithTime[destination].size() - 1;

        for (int i = 0; i < endTime; ++i)
        {
            if (distWithTime[destination][i] < minDistance)
            {
                minDistance = distWithTime[destination][i];
            }
        }

        // Κατασκευή της βέλτιστης διαδρομής
        route.clear();
        route.push_back(destination);

        for (int i = endTime - 1; i >= 0; --i)
        {
            if (distWithTime[destination][i] == minDistance)
            {
                for (int v = 1; v <= n; ++v)
                {
                    if (dist[destination][v] != INT_MAX && canUseRoad(destination, v, i, i + dist[destination][v]) &&
                        distWithTime[v].size() > i + dist[destination][v] && distWithTime[v][i + dist[destination][v]] + dist[destination][v] == minDistance)
                    {
                        route.push_back(v);
                        destination = v;
                        break;
                    }
                }
            }
        }

        reverse(route.begin(), route.end());
        return minDistance;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n);

    int start, end, time, cities;
    cin >> start >> end >> time >> cities;

    g.presidentPath.resize(cities);

    for (int i = 0; i < cities; ++i)
    {
        cin >> g.presidentPath[i];
    }

    for (int i = 0; i < m; ++i)
    {
        int u, v, d;
        cin >> u >> v >> d;
        g.addEdge(u, v, d);
    }

    vector<int> route;
    int minDistance = g.dijkstraWithPresident(start, end, time, route);

    if (minDistance == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << minDistance << endl;
        for (int i = 0; i < route.size(); ++i)
        {
            cout << route[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
