#include <iostream>
#include <vector>
using namespace std;

unsigned long long sam(unsigned long long c, unsigned long long x, unsigned long long n, unsigned long long z) {
    vector<int> bits;
    unsigned long long temp = x;

    while ( temp > 0 ) {
        bits.push_back(temp % 2);
        temp /= 2;
    }

    int l = bits.size();

    for ( int i = l - 1; i >= 0; i-- ) {
        z = z * z % n;
        if ( bits[i] == 1 ) {
            z = z * c % n;
        }
    }

    return z;
}

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

int main() {
    
}