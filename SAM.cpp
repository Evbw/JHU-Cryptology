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

int main() {
    unsigned long long c, x, n, z = 1;

    cout<<"Enter a value for base c: "<<endl;
    cin>>c;
    cout<<"Enter a value for an exponent x: "<<endl;
    cin>>x;
    cout<<"Enter a value for mod n: "<<endl;
    cin>>n;

    z = sam(c, x, n, z);

    cout<<c<<" ^ "<<x<<" mod "<<n<<" = "<<z<<endl;
    return 0;
}