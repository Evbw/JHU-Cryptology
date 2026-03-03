#include <iostream>
#include <cmath>
using namespace std;

long long eea(long long a, long long b) {
    
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