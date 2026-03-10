#include <iostream>
using namespace std;

string to_string_128(unsigned __int128 val) {
    if ( val == 0 ) {
        return 0;
    }
    string s;
    while ( val > 0 ) {
        s = char('0' + val % 10) + s;
        val /= 10;
    }
    return s;
}

unsigned __int128 from_string_128(const string &s) {
    unsigned __int128 val = 0;
    for ( char c : s ) {
        val = val * 10 + (c - '0');
    }
    return val;
}

unsigned __int128 f(unsigned __int128 x, unsigned __int128 n) {
    return (x*x + 1) % n;
}

unsigned __int128 gcd_128(unsigned __int128 x, unsigned __int128 n) {
    while ( n != 0 ) {
        __int128 t = n;
        n = x % n;
        x = t;
    }
    return x;
}

unsigned __int128 pollard_rho(unsigned __int128 n, unsigned __int128 x1, unsigned __int128 &count) {
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

int main() {
    unsigned __int128 n1 = 53081719;
    unsigned __int128 n2 = 44818676050679;
    unsigned __int128 n3 = from_string_128("14690966543846720848264259950499");
    unsigned __int128 x1 = 31;

    unsigned __int128 result;
    unsigned __int128 count;

    result = pollard_rho(n1, x1, count);

    cout<<endl<<"First result is: "<<to_string_128(result)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;
    count = 0;

    result = pollard_rho(n2, x1, count);

    cout<<endl<<"Second result is: "<<to_string_128(result)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;
    count = 0;

    result = pollard_rho(n3, x1, count);

    cout<<endl<<"Second result is: "<<to_string_128(result)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;

    return 0;
}