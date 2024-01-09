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
    vector<pair<int,int>> parents;//the parents and the distance to them
    long distance;//distance to capital
    int speed;
    int p;//the loading time
    City(){
        distance = 0;
    }
    City(const City& parent,int index,long d): parents(parent.parents){
        distance = parent.distance+d;
        pair<int,int> pair(index,d);
        parents.push_back(pair);
    }
};

int main(){
    int n;
    cin >> n;
    vector<Edge> g(n-1);
    vector<long int> lt(n-1), tt(n-1); 
    for(int i = 0; i<n-1; ++i){
        int u,v,d;
        cin >> u >> v >> d;
        Edge e(u,v,d);
        g[i] = e;
    } 
}