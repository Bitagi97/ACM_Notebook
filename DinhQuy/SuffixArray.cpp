#include <bits/stdc++.h>

using namespace std;

const int MAXN  =   100000 + 10;

string S;
int sa[MAXN], temp[MAXN], pos[MAXN], lcp[MAXN], gap, n, nxt[MAXN];

bool cmp(int i, int j)
{
    if (pos[i] != pos[j])  return pos[i] < pos[j];
    i+= gap;
    j+= gap;

    return ((i <= n && j <= n) ? (pos[i] < pos[j]) : (i > j));
}

void  built_RMQ()
{
    memset(RMQ, 0x3c, sizeof(RMQ));
    for(int i = 1; i <= n; i++)
        RMQ[i][0] = lcp[i];
    for (int j = 1; (1 << j) <= n; j++)
          for (int i = 1; i<= n; i++)
              RMQ[i][j] = min(RMQ[i][j - 1], RMQ[i + (1 << (j - 1))][j - 1]);
}
int minn(int i, int j)
{
    int __log = 1;
    while(__log <= (j - i + 1)/2) __log*= 2;
    return min(RMQ[i][__log], RMQ[j - (1<<__log)][__log]));
}

int main()
{
    cin>> S;
    n = S.length();
    for(int i =1; i<= n; i++)
    {
        sa[i] = i;
        pos[i] = S[i - 1];
    }
    for(gap = 1;; gap *=2){
        sort(sa + 1, sa + n + 1, cmp);
        for(int i = 1; i < n; i++)
            temp[i+1] = temp[i] + cmp(sa[i], sa[i + 1]);
        for(int i =1; i <= n; i++)
            pos[sa[i]] = temp[i];
        if (gap >= n) break;
    }

    for(int i = 1; i<= n; i++)
        cout<< sa[i] - 1 <<'\n';
    for (int i = 1, k = 0; i <= n; i++) if (pos[i] != n)
		{
			for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
			++k;
			lcp[pos[i]] = k;
			if (k)--k;
		}
}

