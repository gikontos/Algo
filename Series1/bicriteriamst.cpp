#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int gcd (int a, int b){
    while(a>0 && b>0){
        if (a>b) a = a%b;
        else b = b%a;
    }
    return(a+b);
}

struct Edge{
    int u,v,p,w;
    Edge(int a, int b, int c, int d){
        u = a;
        v = b;
        p = c;
        w = d;
    }
};

bool comp(const Edge &e1, const Edge &e2){
    return static_cast<double>(e1.p) / e1.w > static_cast<double>(e2.p) / e2.w;
}

class UF {
    int* parent;
    int* rank;

public:
    UF(int n) {
        parent = new int [n];
        rank = new int [n];
        for(int i = 0; i<n; ++i){
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i){
        if(parent[i] == -1) 
            return i;
        return parent[i] = find(parent[i]); 
    }

    void unite (int x, int y){
        int s1 = find(x);
        int s2 = find(y);
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    }
};

class Graph {
    int n;
    vector<Edge> l;

public:
    Graph(int V) {this->n=V;}

    void addEdge(int u,int v,int p,int w){
        l.push_back(Edge(u,v,p,w));
    }

    void mst(){
        sort(l.begin(),l.end(),comp);
        UF s(n);
        int profit = 0 , weight = 0;
        for(auto edge:l){
            int k = edge.p;
            int x = edge.u-1;
            int y = edge.v-1;
            int c = edge.w;
            if(s.find(x)!=s.find(y)){
                s.unite(x,y);
                profit+=k;
                weight+=c;
            }
        }
        int d = gcd(profit,weight);
        cout << profit/d << " " << weight/d << "\n";
    }
};

int main(){
    int m,n;
    cin >> n >> m;
    Graph g(n);
    for(int i=0; i<m; ++i){
        int u,v,p,w;
        cin >> u >> v >> p >> w;
        g.addEdge(u,v,p,w);
    }
    g.mst();   
}