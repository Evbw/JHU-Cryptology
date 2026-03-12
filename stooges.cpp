#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long long eea(long long a, long long b, long long &s, long long &t) {

    long long a0 = a;
    long long b0 = b;
    long long t0 = 0;
    long long s0 = 1;
    long long q = a0/b0;
    long long r = a0-q*b0;
    
    long long temp;

    while ( r > 0 ) {
        temp = t0-q*t;
        t0 = t;
        t = temp;
        temp = s0-q*s;
        s0 = s;
        s = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0-q*b0;
    }
    r = b0;

    return r;
}

long long mod_inverse(long long a, long long b) {
    long long a0 = a;
    long long b0 = b;
    long long t0 = 0;
    long long t = 1;
    long long q = a0/b0;
    long long r = a0-q*b0;
    long long temp;

    while ( r > 0 ) {
        temp = ((t0-q*t)%a+a) % a;
        t0 = t;
        t = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0-q*b0;
    }

    if ( b0 != 1 ) {
        cout<<b<<" has no inverse modulo "<<a<<"."<<endl;
        return -1;
    }
    
    return t;
}

long long crt(vector<long long> a, vector<long long> m) {

    long long k = a.size();

    __int128 M = 1;
    for ( long long i = 0; i < k; i++ ) {
        M *= m[i];
    }

    __int128 x = 0;
    __int128 Mi = 0;
    __int128 term = 0;
    long long yi = 0;
    for ( long long i = 0; i < k; i++ ) {
        Mi = M/m[i];
        yi = mod_inverse(m[i], static_cast<long long>(Mi % m[i]));
        term = static_cast<__int128>(a[i]) * (Mi % M);
        term %= M;
        term *= yi;
        term %= M;
        x = (x + term) % M;
    }

    return x;
}

long long cube_root(__int128 n) {
    long long lo = 0;
    long long hi = 1;

    while ( hi*hi*hi < n ) {
        hi *= 2;
    }

    while ( lo <= hi ) {
        long long mid = lo + (hi -lo) / 2;
        __int128 cube = static_cast<__int128>(mid)*mid*mid;

        if ( cube == n ) {
            return mid;
        }
        else if ( cube < n ) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout<<"No exact cube root found"<<endl;
    return hi;
}

int main() {

    vector<long long> n = {25777, 22879, 66277};
    vector<long long> c1 = {19052, 4546, 44619};
    vector<long long> c2 = {1708, 11733, 19731};

    __int128 m1_cubed = crt(c1, n);

    long long m1 = cube_root(m1_cubed);
    cout<<"The first message is = "<<m1<<endl;

    //for ( long long i = 0; i < k; i ++ ) {
    //    cout<<result<<" mod "<<m[i]<<" = "<<result%m[i]<<endl;
    //}

    return 0;
}