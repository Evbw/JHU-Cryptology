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

long long mod_inverse(long long totient, long long e) {
    long long t = 1;
    long long s = 0;
    long long gcd = eea(totient, e, s, t);

    if ( gcd != 1 ) {
        cout<<"Error: e = "<<e<<" has no inverse modulo "<<totient<<"."<<endl;
        return -1;
    }

    t = ((t%totient)+totient)%totient;
    return t;
}

//Note that much of this code is refactored from an assignment I did as a team in Assembly for prerequisite class
//https://github.com/Evbw/RSATeam2/blob/master/RSA.s
int main() {

    long long p = 853;
    long long q = 223;
    long long n = (p*q);
    long long totient = (p-1)*(q-1);
    long long e;

    cout<<endl<<"The value for p and q are 853 and 223, respectively."<<endl;
    cout<<"n = p * q = "<<n<<endl;
    cout<<"phi(n) = (p - 1) * (q - 1) = "<<totient<<endl;

    cout<<"Enter a value for the public exponent, e"<<endl;
    cout<<"(Value must be between 1 and "<<totient<<", and coprime to "<<totient<<"):"<<endl;
    cin>>e;
    
    long long d = mod_inverse(totient, e);
}