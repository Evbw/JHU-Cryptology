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

//Cribbed mulmod algorithm from https://www.geeksforgeeks.org/dsa/how-to-avoid-overflow-in-modular-multiplication/
unsigned __int128 mulmod(unsigned __int128 a, unsigned __int128 b, unsigned __int128 mod)
{
    unsigned __int128 res = 0; // Initialize result
    a = a % mod;
    while (b > 0)
    {
        // If b is odd, add 'a' to result
        if (b % 2 == 1)
            res = (res + a) % mod;

        // Multiply 'a' with 2
        a = (a * 2) % mod;

        // Divide b by 2
        b /= 2;
    }
    // Return result
    return res % mod;
}

unsigned __int128 f(unsigned __int128 x, unsigned __int128 n) {
    return (mulmod(x, x, n)+ 1) % n;
}

unsigned __int128 gcd_128(unsigned __int128 x, unsigned __int128 n) {
    while ( n != 0 ) {
        unsigned __int128 t = n;
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
        count++;
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

    unsigned __int128 p;
    unsigned __int128 q;
    unsigned __int128 count = 1;    //Starting the count at 1 for the start of the differential loop

    p = pollard_rho(n1, x1, count);
    q = n1/p;

    cout<<endl<<"First result is p = "<<to_string_128(p)<<", q = "<<to_string_128(q)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;
    count = 1;

    p = pollard_rho(n2, x1, count);
    q = n2/p;

    cout<<endl<<"Second result is p = "<<to_string_128(p)<<", q = "<<to_string_128(q)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;
    count = 1;

    p = pollard_rho(n3, x1, count);
    q = n3/p;

    cout<<endl<<"Third result is p = "<<to_string_128(p)<<", q = "<<to_string_128(q)<<" and it took "<<to_string_128(count)<<" iterations"<<endl;

    return 0;
}