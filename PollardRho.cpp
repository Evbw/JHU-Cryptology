#include <iostream>
using namespace std;

__int128 f(__int128 x, __int128 n) {
    return (x*x + 1) % n;
}

__int128 gcd_128(__int128 x, __int128 n) {
    while ( n != 0 ) {
        __int128 t = n;
        n = x % n;
        x = t;
    }
    return x;
}

__int128 pollard_rho(__int128 n, __int128 x1) {
    __int128 x = x1;
    __int128 xp = f(x, n);
    __int128 xdiff = x - xp;
    if ( xdiff < 0 ) {
        xdiff = -xdiff;
    }
    __int128 p = gcd_128(xdiff, n);

    while ( p == 1 ) {
        x = f(x, n);
        xp = f(xp, n);
        xp = f(xp, n);
        xdiff = x - xp;
        if ( xdiff < 0 ) {
            xdiff = -xdiff;
        }
        p = gcd_128(xdiff, n);
    }

    if ( p == n ) {
        return 0;
    }
    return p;
}

__int128 factor_n(__int128 n) {
    for ( __int128 x1 = 2; x1 < 100; x1++ ) {
        __int128 p = pollard_rho(n, x1);
        if (p != 0 && p != n) {
            return p;
        }
    }
    return 0;
}