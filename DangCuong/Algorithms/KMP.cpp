#include <bits/stdc++.h>

using namespace std;

const int MaxN = 1000005;

string s1,s2;
int pre[MaxN];
int KMP(string s2,string s1)
{
    int result = 0;
    int n = s2.length();
    int m = s1.length();
    if (n > m) return 0;
    int j = -1;
    pre[0]=-1;
    for(int i=1;i<n;i++){
        while(j>=0 && s2[j+1]!=s2[i]) j=pre[j];
        if(s2[j+1]==s2[i]) j++;
        pre[i]=j;
    }
    j = -1;
    for(int i=0;i<m;i++){
        while(j>=0 && s2[j+1]!=s1[i]) j= pre[j];
        if(s2[j+1]==s1[i]) j++;
        if(j==n-1){
            cout << i-n+1<<" ";
            result ++;
            j=pre[n-1];
        }
    }
    cout << endl;
    return result;
}
int main()
{
    cin >> s1;
    cin >> s2;
    cout << KMP(s2,s1); // number s2 in s1
}
