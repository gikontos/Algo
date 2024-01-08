#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
    int u, v, d;
    Edge(int k, int l, int m){
        u = k;
        v = l;
        d = m;
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