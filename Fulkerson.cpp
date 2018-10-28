#include <bits/stdc++.h>
using namespace std;

const int N = 1003, oo = 0x3c3c3c3c;
int n, m, S, T;
int d[N], c[N][N], f[N][N];
int Dfs[N], t=0;
vector<int> a[N];

bool bfs(int S, int T) {
    memset(d, 0, sizeof d);
    queue<int> qu;
    qu.push(S); d[S]=1;
    while (qu.size()) {
        int u=qu.front(); qu.pop();
        if (u==T) return true;
        for (int  i=0,v=1;i<a[u].size(),v=a[u][i];i++)
            if (!d[v] && f[u][v]<c[u][v])
            { qu.push(v); d[v]=d[u]+1; }
    }
    return false;
}

int visit(int u, int Min) {
    if (u==T) return Min;
    if (Dfs[u]!=t) Dfs[u]=t;
    else return 0;

    for (int  i=0,v=1;i<a[u].size(),v=a[u][i];i++)
        if (f[u][v]<c[u][v])
        if (Dfs[v]!=t && d[v]==d[u]+1)
        if (int x = visit(v, min(Min, c[u][v]-f[u][v])))
        { f[u][v]+=x; f[v][u]-=x; return x; }
    return 0;
}

main() {
    cin >> n >> m >> S >> T;
    for (int i=1; i<=m; i++) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        a[x].push_back(y);
        a[y].push_back(x);
        c[x][y] += z;
    }
    for(int i=1;i<=n;i++) a[i].push_back(0);
    int Sum = 0;
    while (bfs(S, T)) {
        while (int x = (t++, visit(S, oo))) {
            Sum += x;
        }
    }
    cout << Sum << endl;
}
