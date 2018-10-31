//NOTYET
#include <bits/stdc++.h>
#define     next    __next
using namespace std;

struct Node{
    int L, R;
    int val;
    Node *Left, *Right;
    Node(){};
    Node(int LL ,int RR, int vval = 0): L(LL), R(RR), val(vval) {};
    Node* Upd(int u, int i)
    {
        Node* v = new Node(L, R);
        int mid = (L + R) /2;
        if (L==R && R==u){
            v->val = i;
            return v;
        }
        if (u <= mid){
            if (Left!= NULL)
                v->Left = Left->Upd(u, i);
            v->Right = Right;
        }
        else{
            if (Right!= NULL)
                v->Right = Right->Upd(u, i);
            v->Left  = Left;
        }


        v->val = 0;
        if (Left!= NULL) v->val+= v->Left->val;
        if (Right!= NULL) v->val+= v->Right->val;

        return v;
    }
    int Query(int u, int v)
    {
        if (v<L||R<u) return 0;
        if (L<=u && v<=R) return val;
        int     ret    =    0;
        if (Left!= NULL)  ret+= Left->Query(u, v);
        if (Right!= NULL) ret+= Right->Query(u, v);
        return ret;

    }
};
Node* root[30000 + 10];
int n, A[30000 + 10], next[30000+10];

Node* Build(int i, int j)
{
    Node* N = new Node(i, j) ;
    N->L = i;
    N->R = j;
    if (i == j){
        N->val = A[i];
        return N;
    }
    int mid = (i + j) / 2;
    N->Left = Build(i, mid);
    N->Right = Build(mid+1, j);
    N->val = N->Left->val + N->Right->val;
    return N;
}


map< int, int > m;

int main()
{
    freopen("Test.inp","r",stdin);
    cin >> n;
    for(int i = 1; i<=n; i++)
        cin>>A[i];
    for(int i = 1; i<= n; i++)
        m[A[i]] = n + 1;
    for(int i = n; i>=1; i--){
        next[i] = m[A[i]];
        m[A[i]] = i;
    }
    root[n+1] = Build(1, n + 1);
    for(int i = n; i >= 1; i--){
        root[i] = root[i+1]->Upd( next[i] , 1 );
    }
    int leftQuery, rightQuery, Q;
   cin>>   Q   ;
    while(Q--){
        cin>> leftQuery >>  rightQuery  ;
        cout<<(n - root[leftQuery]->Query(1 , rightQuery) + 1)<<'\n';
    }
}
/*

5
1 1 2 1 3
3
1 5
2 4
3 5

*/
