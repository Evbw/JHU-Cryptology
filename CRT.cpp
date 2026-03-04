#include <iostream>
#include <vector>
using namespace std;

long long mod_inverse(long long a, long long b) {
    
}

int main() {
    vector<long long> a = {29683, 14495, 136776};
    vector<long long> m = {163659, 146921, 193331};

    int k = a.size();

    __int128 M = 1;
    for ( int i = 0; i < k; i++ ) {
        M *= m[i];
    }

    __int128 x = 0;
    __int128 Mi = 0;
    long long yi = 0;
    for ( int i = 0; i < k; i++ ) {
        Mi = M/m[i];
        yi = mod_inverse(m[i], (long long)(Mi % m[i]));
    }

}