#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int u, v, c, f;
    Edge(int u,int v, int c,int f):u(u), v(v), c(c), f(f){};
    Edge(){};
};
struct  Flow{
    int n, s, t;
    vector< int > dist;
    vector< Edge > e;
    vector< vector< int > > adj;
    Flow(){};
    Flow(int n): n(n), dist{n + 1}, adj(n + 1){
        e.clear();
        dist.clear();
        for(int i = 1; i <= n; i++) adj[i].clear();
    }
    void addEdge(int u,int v, int c)
    {
        adj[u].push_back((int) e.size());
        e.push_back(Edge(u, v, c, 0));
        adj[v].push_back((int) e.size());
        e.push_back(Edge(v, u, 0, 0));
    }
    bool Bfs()
    {
        queue< int > q;;
        for(int i = 0; i <= n; i++) dist[i] = -1;
        dist[s] = 0;
        q.push(s);
        vector< int > ::iterator it;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(it = adj[u].begin(); it != adj[u].end(); it++){
                int v = e[*it].v ;
            if (e[*it].c > e[*it].f && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                }
            }
        }
        return (dist[t] > -1);
    }

    int Dfs(int u, int __min)
    {
        if (u == t) return __min;
        vector< int > ::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); it++){
            int v = e[*it].v ;
            if (e[*it].c > e[*it].f && dist[v] == dist[u] + 1) {
                int go = Dfs(v, min(__min, e[*it].c - e[*it].f));
                if (go){
                    e[*it].f+= go;
                    e[(*it)^1].f-= go;
                    return go;
                }
            }
        }
        return 0;
    }

    int max_flow(int _s, int _t)
    {
        s = _s; t = _t;
        int cost = 0;
        while(Bfs()){
            while(1){
                int val = Dfs(s, 1e9);
                if (val) cost+= val; else break;
            }
        }
        return cost;
    }
};
int n, m, s, t;
int main()
{
    cin >> n >> m >> s >> t;
    Flow  flow(n);
    int u, v, __c;
    for(int i = 1; i <= m; i++){
        cin>> u >> v >> __c;
        flow.addEdge(u, v, __c);
    }
    cout<< flow.max_flow(s, t);
    return 0;
}
