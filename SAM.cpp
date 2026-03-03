#include <iostream>
#include <vector>
using namespace std;

unsigned long long sam(unsigned long long x, unsigned long long c, unsigned long long n, unsigned long long z) {
    vector<int> bits;
    unsigned long long temp = c;

    while ( temp > 0 ) {
        bits.push_back(temp % 2);
        temp /= 2;
    }

    int l = bits.size();

    for ( int i = l - 1; i >= 0; i-- ) {
        z = z * z % n;
        if ( bits[i] == 1 ) {
            z = z * x % n;
        }
    }

    return z;
}

int main() {
    unsigned long long x, c, n, z = 1;

    cout<<"Enter a value for base c: "<<endl;
    cin>>c;
    cout<<"Enter a value for an exponent x: "<<endl;
    cin>>x;
    cout<<"Enter a value for mod n: "<<endl;
    cin>>n;

    z = sam(x, c, n, z);
}