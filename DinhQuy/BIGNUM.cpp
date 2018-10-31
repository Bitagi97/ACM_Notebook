#include <bits/stdc++.h>

using namespace std;

typedef   long  long     llint;

llint __pow(int k)
{
    if (!k)     return 1;
    return 10 * __pow(k - 1);
}
struct bigint{
    vector< llint > digits;
    bigint(){};
    bigint(int x){ digits.push_back(x); }
    void output() {
        int n = digits.size();
        printf( "%d", digits[--n] );
        while( n > 0 ) printf( "%09d", digits[--n] );
        printf( "\n" );
    }
    void refine()
    {
       llint carry = 0, __;
       for( int i = 0; i < digits.size(); i++){
            __ = carry;
            carry = ( digits[i] + carry )/ 1000000000;
            digits[i] = (digits[i] + __) % 1000000000;
       }
       if (carry)  digits.push_back( carry );
    }
    void checker()
    {
        while (digits.size() > 1 && digits.back() == 0)  digits.pop_back();
    }
    void operator += (const bigint &b ) {
        int carry = 0;
        for( int i = 0; i < digits.size() || i < b.digits.size() || carry; ++i ) {
            int x = carry;
            if( i < digits.size() ) x += digits[i];
            if( i < b.digits.size() ) x += b.digits[i];
            carry = x >= 1000000000;
            if( carry ) x -= 1000000000;
            if( i < digits.size() ) digits[i] = x;
            else digits.push_back( x );
        }
        refine();
        checker();
    }
    void operator-= (const bigint& b)
    {
        int carry = 0;
        for( int i = 0; i < digits.size() || i < b.digits.size() || carry; ++i ) {
            int x = 0, y = carry;
            if( i < digits.size() ) x = digits[i];
            if( i < b.digits.size() ) y += b.digits[i];
            if (x < y){
                carry = 1;
                x+=  1000000000;
         }  else carry = 0;
         int ret    =    0;
         ret = x - y;
         if( i < digits.size() ) digits[i] = ret;
         else digits.push_back( ret );
      }
      refine();
      checker();
   }
   void operator*=(const bigint& b)
   {
        bigint that;
        that.digits = vector< llint > (digits.size() + b.digits.size(), 0);
        for(int i = 0 ; i < digits.size(); i++){
            for(int j = 0; j < b.digits.size(); j++)
                that.digits[i + j] += digits[i] * b.digits[j];
            that.refine();
        }
        that.checker();
        digits = that.digits;
   }
   bool operator<=(const bigint& b)
   {
       if (digits.size() != b.digits.size())
            return digits.size() < b.digits.size();
       for(int i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != b.digits[i])   return digits[i] < b.digits[i];
       return 1;
   }
   void convert(string s)
   {
       digits.clear();
       int last  =   0, cur = 0;
       for(int i = s.length() - 1; i >= 0; i--){
            last = last + (s[i] - '0') * __pow(cur);
            cur++;
            if (last >= 100000000|| cur >= 9){
                digits.push_back(last);
                last = 0;
                cur = 0;
            }
       }
       if (last)  digits.push_back(last);
       refine();
       checker();
   }
};

string s;
bigint  A, B, temp;
int main()
{
    cin>> s;
    A.convert( s );
    cin>> s;
    B.convert( s );
    temp = B;
    temp+= A;
    temp.output();
    temp = B;
    if (B <= A){
        temp = A;
        temp-= B;
        temp.output();
    } else {
        temp = B;
        temp-= A;
        cout<<"-";  temp.output();
    }
    temp = A;
    temp*= B;
    temp.output();
    return 0;
}
