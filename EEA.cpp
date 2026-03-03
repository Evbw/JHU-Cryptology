#include <iostream>
#include <cmath>
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

int main() {
    
    long long a, b, r;

    cout<<"Enter a value for a: "<<endl;
    cin>>a;
    cout<<"Enter a value for b: "<<endl;
    cin>>b;

    long long t = 1;
    long long s = 0;

    r = eea(a, b, s, t);

    cout<<endl<<"gcd("<<a<<", "<<b<<") = "<<r<<endl;
    cout<<"s = "<<s<<endl;
    cout<<"t = "<<t<<endl;
    if ( ((s * a) + (t * b)) == r )  {
        cout<<s<<" * "<<a<<" + "<<t<<" * "<<b<<" = "<<(s * a) + (t * b)<<endl;
        cout<<"Result is valid."<<endl;
    }
    else {
        cout<<s<<" * "<<a<<" + "<<t<<" * "<<b<<" = "<<(s * a) + (t * b)<<endl;
        cout<<"Result is invalid."<<endl;
    }
    return 0;
}