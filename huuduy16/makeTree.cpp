#include<bits/stdc++.h>
#define llong long long
using namespace std;
void solve(int minN, int maxN, int minC, int maxC)
    {
        n=random(minN,maxN);
        cout<<n<<'\n';
        for (int i=1; i < n; i++){
            int u=i, v=random(1,u-1);
            int cost=random(minC,maxC);
            cout<<u<<' '<<v;
            if (minC > maxC) cout<<' 'cost;
            cout<<'\n';
            a[u].push_back(MP(v,cost));
            a[v].push_back(MP(u,cost));
        }
    }
int main()
{
    srand(time(NULL));
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    ios::sync_with_stdio(0);
    return 0;
}
