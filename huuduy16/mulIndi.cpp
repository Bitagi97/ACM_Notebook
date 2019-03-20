#define llong long long
#define MOD 1000000007
llong add(llong A, llong  B){A+=B; while (A >= MOD) A-=MOD; return A;}
llong mulInd(llong A, llong B)
    {
        if (B == 0) return 0;
        llong rs=mul(A,B/2); rs=add(rs,rs);
        if (B%2 == 1) rs=add(rs,A);
        return rs;
    }
#undef llong
#undef MOD
