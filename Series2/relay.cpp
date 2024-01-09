#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

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

int main(){
    int n;
    cin >> n;
    vector<City> Cities(n+1);
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
}