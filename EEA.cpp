#include <iostream>
#include <cmath>
using namespace std;

long long eea(long long a, long long b) {
    long long a0 = a;
    long long b0 = b;
    long long t0 = 0;
    long long t = 1;
    long long s0 = 1;
    long long s = 0;
    long long q = a0/b0;
    long long r = a0-q*b0;

    while ( r > 0 ) {
        
    }
}

int main() {
    
    long long a, b, x;
    cout<<"Enter a value for a: "<<endl;
    cin>>a;
    cout<<"Enter an exponent (a value of 0 will be disregarded and behave as a value of 1): "<<endl;
    cin>>x;
    if ( x == 0 ) {
        x = 1;
    }
    a = pow(a, x);
    cout<<"Enter a value for b: "<<endl;
    cin>>b;

    eea(a, b);
}