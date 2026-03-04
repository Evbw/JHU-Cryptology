#include <iostream>
#include <vector>
using namespace std;

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

int main() {
    vector<long long> a = {29683, 144995, 136776};
    vector<long long> m = {163659, 146921, 193331};

    int k = a.size();

    __int128 M = 1;
    for ( int i = 0; i < k; i++ ) {
        M *= m[i];
    }

    __int128 x = 0;
    __int128 Mi = 0;
    __int128 term = 0;
    long long yi = 0;
    for ( int i = 0; i < k; i++ ) {
        Mi = M/m[i];
        yi = mod_inverse(m[i], static_cast<long long>(Mi % m[i]));
        term = static_cast<__int128>(a[i]) * (Mi % M);
        term %= M;
        term *= yi;
        term %= M;
        x = (x + term) % M;
    }

    long long result = static_cast<long long>(x);
    cout<<"x = "<<result<<endl;

    for ( int i = 0; i < k; i ++ ) {
        cout<<result<<" mod "<<m[i]<<" = "<<result%m[i]<<endl;
    }

    return 0;
}